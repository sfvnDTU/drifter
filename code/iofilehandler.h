/**
 *  Project:        Parmugit
 *  Class:          IoFileHandler
 *  Created by:     Jesper L. Hinrich, Julian K. Larsen and Soeren F. V. Nielsen
 *  Affiliation:    Technical University of Denmark
 *  Date:           January 2015
 */

#ifndef IOFILEHANDLER_H
#define IOFILEHANDLER_H


#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <vector>

class IoFileHandler
{
    public:
        IoFileHandler(); // default dummy constructor
        IoFileHandler(std::string);
        IoFileHandler(std::string,bool);

        int read_graph();
        int read_test_case();


        // Get functions
        std::list<std::pair<int,int>> getDataEl();
        std::list<std::pair<int,int>> getTreeEl();
        std::vector<int> getLeafDataRelation();
        std::string getFilename();
        double getAlpha();
        double getBeta();
        int getRhoPlus();
        int getRhoMinus();
        double getLlike();

        // Set functions
        void setDataEl(std::list<std::pair<int,int>>);
        void setTreeEl(std::list<std::pair<int,int>>);
        void setLeafDataRelation(std::vector<int>);
        void setFilename(std::string);
        void setAlpha(double);
        void setBeta(double);
        void setRhoPlus(int);
        void setRhosMinus(int);
        void setLlike(double);

        // Print functions
        std::string toDataEdgeListString();

    private:
        bool write;
        std::string filename;
        // std::string file_path;
        std::list<std::pair<int,int>> data_edge_list;
        std::list<std::pair<int,int>> tree_edge_list;
        std::vector<int> leaf_data_relation;
        double alpha, beta;
        int rho_plus, rho_minus;
        double llike;
};

#endif // IOFILEHANDLER_H
