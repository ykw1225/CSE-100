#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP




using namespace std;

class ActorGraph {
   protected:

     
   public:
      ActorGraph(void);
      ~ActorGraph();

   /**
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as
     * 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
     bool loadFromFile(const char* in_filename, bool use_weighted_edges);

};


#endif // ACTORGRAPH_HPP
