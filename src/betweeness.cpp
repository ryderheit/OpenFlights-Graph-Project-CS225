#include <algorithm>
#include <iostream>
#include <fstream>

#include "graph.hpp"

void Airport::to(const std::size_t dst, Route & r) const {
    for (const Route & rt : adjList) {
        if (rt.dest_pos == dst) {
            r = rt;
            return;
        }
    }
}

void Graph::generateCentrality(std::size_t minSize) {
    //Run FW first!
    if (next_.size() != airports_.size()) {
        printf("Please run Floyd-Warshall first!\n");
        return;
    }
    //Make room for all airports right away
    btwn_.resize(airports_.size(), 0);
    printf("Centrality Progress:\n");
    //For each route
    for (std::size_t i = 0; i < numAirports_; ++i) {
        if (airports_[i].adjList.size() < minSize) continue;
        for (std::size_t j = 0; j < numAirports_; ++j) {
            if (airports_[j].adjList.size() < minSize) continue;
            auto v = pathHelper(airports_[i].iata, airports_[j].iata);
            //Skip routes with no middle
            if (v.size() < 3) continue;
            double str = 0;
            Route r;
            //Calculate the strength of the route
            for (std::size_t s = 0; s < v.size() - 1; ++s) {
                const Airport & cur = airports_[v[s]];
                const Airport & nxt = airports_[v[s+1]];
                cur.to(nxt.id, r);
                str += r.routes * r.weight;
            }
            //Add that to the centrality of each airport
            for (std::size_t i = 1; i < v.size() - 1; ++i) {
                btwn_[v[i]] += str;
            }
            std::cout << "\r";
            std::cout << i << "," << j << std::flush;
        }
    }

    printf("\r%lu,%lu\n\n", numAirports_, numAirports_);

    //Normalize. There are many ways to do this; another is to 
    //just divide by max to get centrality 'as a percent of'
    //the most central airport. This normalizes to [0,1]
    auto minmax = std::minmax_element(btwn_.begin(), btwn_.end());
    float max = *minmax.second, min = *minmax.first;
    for (float & c : btwn_) {
        c = (c - min) / (max - min);
    }
}

std::pair<std::string, std::string> Graph::minmax() const {
    //Self-explanatory
    std::size_t max = 0, min = 0;
    float curmax = std::numeric_limits<float>::min(), curmin = std::numeric_limits<float>::max();
    for (std::size_t i = 0; i < btwn_.size(); ++i) {
        if (btwn_[i] > curmax) {
            curmax = btwn_[i];
            max = i;
        }
        if (btwn_[i] < curmin) {
            if (airports_[i].adjList.size() == 0) continue;
            curmin = btwn_[i];
            min = i;
        }
    }
    return { airports_[min].name(), airports_[max].name() };
}

float Graph::centrality(const std::string & src) const {
    //Self explanatory
    auto it = name_map_.find(src);
    if (it == name_map_.end()) return std::numeric_limits<float>::quiet_NaN();
    return btwn_[it->second];
}

std::string Airport::name() const {
    if (iata.empty()) return icao;
    return iata;
}

void Graph::writeBC(const std::string & filename) const {
    std::ofstream file{filename};
    for (auto i : btwn_) {
        std::string s = std::to_string(i);
        file.write(s.c_str(), s.size());
        file.put(',');
    }
    file.close();
}

void Graph::readBC(const std::string & filename) {
    std::ifstream file{filename};
    if (!file.is_open()) {
        std::cerr << "Bad Filename!" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);
    auto v = stringSplit(line);
    btwn_.resize(v.size() - 1);
    for (std::size_t i = 0; i < v.size() - 1; ++i) {
        btwn_[i] = std::stof(v[i]);
    }
}