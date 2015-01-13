//============================================================================
// Name        : test.cpp
// Author      : Søren
// Version     :
// Copyright   : It is OURS!!
// Description : Test function
//============================================================================

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <dirent.h>
#include <cmath>
#include "barebones_tree.h"

using namespace std;

int main()
{
    cout << "!!!Hello Test-World!!!" << endl;
    // Tolerance on likelihood result
    double epsilon = 1e-12;

    string dir_str =  "test/test_files/";
    // For each test file in test_files directory
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dir_str.c_str())) != NULL)
    {
        /* For all files and directories within directory */
        int number_files_read = 0;

        // Collect all test cases with same number of data nodes
        list<double> llike_all_n3, llike_all_n3_true;
        list<double> llike_all_n4, llike_all_n4_true;
        // Test statistics
        int num_passed = 0;
        int num_failed = 0;

        while ((ent = readdir (dir)) != NULL)
        {
            string test_file_name(ent->d_name);
            if (test_file_name == "." || test_file_name == ".." || test_file_name.back() == '~' || test_file_name[0] == '.')
            {
                cout << "Skipping non-interesting stuff.." << endl;
                continue;
            }
            // Read in test file
            cout << "Reading file '" << test_file_name << "..." << endl;
            ifstream inStream(dir_str+test_file_name); //
            //ifstream inStream(ent->d_name); //
            if (!inStream)
            {
                throw runtime_error("Could not open the desired file");
            }


            // Reading number of data nodes and edges
            int number_data_nodes,number_data_edges;
            inStream >> number_data_nodes;
            inStream >> number_data_edges;

            // Reading edge list
            list<pair<int,int>> data_edge_list;
            int e1,e2;
            for (int i=0; i!=number_data_edges; ++i)
            {
                inStream >> e1 >> e2;
                pair<int,int> edge (e1,e2);
                data_edge_list.push_back(edge);
            }

            // Reading in number of nodes in entire tree
            int number_nodes_tree;
            inStream >> number_nodes_tree;

            // Reading tree edge list (Parent->Child)
            list<pair<int,int>> tree_edge_list;
            for (int i=0; i!=number_nodes_tree-1; ++i)
            {
                inStream >> e1 >> e2;
                pair<int,int> edge (e1,e2);
                tree_edge_list.push_back(edge);
            }

            // Reading in relation between tree leaves and data nodes
            // - Two lists are created
            list<int> leaf_data_relation, data_leaf_relation;
            list<pair<int,int>> leaf_data; //
            // consider using vectors instead?
            for (int i=0; i!=number_data_nodes; ++i)
            {
                inStream >> e1 >> e2;
                leaf_data_relation.push_back(e1);
                data_leaf_relation.push_back(e2);

                pair<int,int> edge (e1,e2);
                leaf_data.push_back(edge); //
            }

            // Reading in hyperparameters
            double alpha,beta,rho_plus,rho_minus;
            inStream >> alpha >> beta >> rho_plus >> rho_minus;

            // Reading in true log-likelihood
            double llike_true;
            inStream >> llike_true;

            //DEBUG; PRINTING WHOLE EDGE LIST
//            for (list<int>::iterator it = leaf_data_relation.begin(); it!=leaf_data_relation.end(); ++it ){
//                cout << *it;
//            }
//            cout << endl;
//            for (list<int>::iterator it = data_leaf_relation.begin(); it!=data_leaf_relation.end(); ++it ){
//                cout << *it;
//            }
//            cout << endl;

            //TODO: Format into tree-class structure (approriate constructors)
            Tree test_tree = Tree(data_edge_list, tree_edge_list, leaf_data);
            //cout << test_tree.toString() << endl;

            //TODO: Perform tests - evaluate likelihood of tree
            cout << "Local-Likelihood test...";
            double llike_test = test_tree.evaluateLogLikeTimesPrior(alpha,beta,rho_plus,rho_minus);

            // SOMETHING like test_tree.evaluateLikelihood();

            if (abs(llike_test-llike_true)<epsilon)
            {
                cout << "PASSED!" << endl;
                num_passed++;
            }
            else
            {
                cout << "FAILED!" << endl;
                num_failed++;
            }

            // Save result likelihood result
            if (number_data_nodes == 3)
            {
                llike_all_n3.push_back(llike_test);
                llike_all_n3_true.push_back(llike_true);
            }
            if(number_data_nodes == 4)
            {
                llike_all_n4.push_back(llike_test);
                llike_all_n4_true.push_back(llike_true);
            }
            else
            {
                cout << "This number of data nodes is not in stock..." << endl;
            }

            number_files_read++;
        }
        closedir (dir);

        // Print test statistics
        cout << endl << endl;
        cout << "Number of 'local' tests performed: " << number_files_read << endl;
        cout << "PASSES: " << num_passed << endl;
        cout << "FAILS: " << num_failed << endl << endl;

        // Marginal Likelihood Test
        // - Sum of all test cases should be the same as true
        cout << "Performing Marginal Likelihood Test..." << endl;

        // N = 3 nodes
        double marginal_like_test = 0;
        for (list<double>::iterator it = llike_all_n3.begin();
            it!=llike_all_n3.end(); ++it) {
                marginal_like_test += exp(*it);
        }

        double marginal_like_true = 0;
        for (list<double>::iterator it = llike_all_n3_true.begin();
            it!=llike_all_n3_true.end(); ++it) {
                marginal_like_true += exp(*it);
        }
        cout << "Marginal likelihood - 3 leaves TEST: " << marginal_like_test << endl;
        cout << "Marginal likelihood - 3 leaves TRUE: " << marginal_like_true << endl;

        // N = 4 nodes
        marginal_like_test = 0;
        for (list<double>::iterator it = llike_all_n4.begin();
            it!=llike_all_n4.end(); ++it) {
                marginal_like_test += exp(*it);
        }

        marginal_like_true = 0;
        for (list<double>::iterator it = llike_all_n4_true.begin();
            it!=llike_all_n4_true.end(); ++it) {
                marginal_like_true += exp(*it);
        }
        cout << "Marginal likelihood - 4 leaves TEST: " << marginal_like_test << endl;
        cout << "Marginal likelihood - 4 leaves TRUE: " << marginal_like_true << endl;


    }
    else
    {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }



    return 0;
}
