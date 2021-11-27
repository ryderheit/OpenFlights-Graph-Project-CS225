#include <algorithm>
#include <iostream>

#include "graph.hpp"

void Airport::to(const std::size_t dst, Route & r) const {
    //This is slow. We could have each route track its index
    //in its node to do this in constant time
    for (const Route & rt : adjList) {
        if (rt.dest_pos == dst) {
            r = rt;
            return;
        }
    }
}

void Graph::generateCentrality() {
    //Run FW first!
    if (next_.size() != airports_.size()) {
        printf("Please run Floyd-Warshall first!\n");
        return;
    }
    //Make room for all airports right away
    btwn_.resize(airports_.size(), 0);
    printf("Centrality Progress:\n");
    //For each airport
    for (std::size_t i = 0; i < btwn_.size(); ++i) {
        //For each starting airporty
        for (std::size_t j = 0; j < btwn_.size(); ++j) {
            //For each destination airport
            for (std::size_t k = 0; k < btwn_.size(); ++k) {
                //Do not count diagonals
                if (j == k) continue;
                //Get the path
                auto p = pathHelper(airports_[j].iata, airports_[k].iata);
                //If it has >= 2 airports then its a real path
                if (p.size() < 2) continue;
                //We only add the strength of the path if we pass through the node; this keeps track
                bool passthrough = (j == i || k == i);
                Route r;
                float str = 0;
                for (std::size_t s = 0; s < p.size() - 1; ++s) {
                    //Find the route (should always exist in a valid path)
                    p[s].to(p[s+1].id, r);
                    //If we pass through airport i note that
                    if (!passthrough && (p[s].id == i || p[s+1].id == i)) passthrough = true;
                    str += r.weight * r.routes;
                }
                //if we passed through add the strength of the path
                if (passthrough) btwn_[i] += str;
            }
        }
        std::cout << "\r";
        std::cout << i << "/" << numAirports_ << std::flush;
    }

    printf("\r%lu/%lu\n\n", numAirports_, numAirports_);

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
            curmin = btwn_[i];
            min = i;
        }
    }
    return { airports_[min].iata, airports_[max].iata };
}

float Graph::centrality(const std::string & src) const {
    //Self explanatory
    auto it = name_map_.find(src);
    if (it == name_map_.end()) return std::numeric_limits<float>::quiet_NaN();
    return btwn_[it->second];
}