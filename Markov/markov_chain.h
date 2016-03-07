
#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

template <class T> struct Markov_Edge;
template <class T> struct Markov_State;

template <class T>
class Markov_Chain
{
public:
    Markov_Chain();
    ~Markov_Chain();

    //Adds event to chain with previous state information
    void Add_Event(T last_event, T current_event);

    //Adds a single event without a previous state
    void Add_Event(T current_event);

    //Output randomized state sequence
    std::vector<T> Output_Random_Sequence (int output_length);

    //Output current chain status to console
    void To_String();

    // Every Markov state is indexed by m_map using a data string
    std::map<T,Markov_State<T>> m_map;

};

template <class T>
struct Markov_State
{
    T data;       //Data that corresponds to this state
    unsigned int num_events;//Number of times this state has occured given the input data
    Markov_Edge<T>* edge_list; //List containing all edges to a next possible state
};

template <class T>
struct Markov_Edge
{
    unsigned int event_rate; //Number of time this edge has been taken from previous state given the input data
    Markov_State<T>* next_state;//Next state corresponding to this edge
    Markov_Edge<T>* next_edge;  //Next edge within the edge list
};

////////// - MARKOV CHAIN IMPLEMENTATION - //////////

template <class T>
Markov_Chain<T>::Markov_Chain()
{
}

template <class T>
Markov_Chain<T>::~Markov_Chain()
{
    Markov_Edge<T>* current;
    Markov_Edge<T>* next;
    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        current = ((Markov_State<T>)iterator->second).edge_list;
        next = NULL;

        while (current != NULL)
        {
            next = current->next_edge;
            delete current;
            current = next;
        }
    }
}

//Insert new event with no edges
template <class T>
void Markov_Chain<T>::Add_Event(T current_event)
{
    if (m_map.count(current_event) == 0)
    {
        Markov_State<T> new_state;
        new_state.num_events = 0;
        new_state.data = current_event;
        new_state.edge_list = NULL;

        m_map.insert(std::pair<T,Markov_State<T>>(current_event,new_state));
    }
}

//Insert new event with an edge from the previous state:
// Last Event -> Current Event
template <class T>
void Markov_Chain<T>::Add_Event(T last_event, T current_event)
{
    //If the map contains this state already, increase event count
    if (m_map.count(current_event))
    {
        m_map[current_event].num_events++;
    }
    else
    //Else create new state for this event
    {
        Markov_State<T> new_state;
        new_state.num_events = 1;
        new_state.data = current_event;
        new_state.edge_list = NULL;
        m_map.insert(std::pair<T,Markov_State<T>>(current_event,new_state));
    }

    //Update the edge that points from the last to the current event
    Markov_Edge<T>* index = m_map[last_event].edge_list;

    if (index == NULL)
    {
        m_map[last_event].edge_list = new Markov_Edge<T>;
        index = m_map[last_event].edge_list;
        index->event_rate = 1;
        index->next_state = &m_map[current_event];
        index->next_edge = NULL;
    }
    else
    {
        while (index->next_edge != NULL && index->next_state->data != current_event)
        {
            index = index->next_edge;
        }

        if (index->next_state->data != current_event)
        {
            index->next_edge = new Markov_Edge<T>;
            index = index->next_edge;
            index->event_rate = 1;
            index->next_state = &m_map[current_event];
            index->next_edge = NULL;
        }
        else
        {
            index->event_rate++;
        }
    }

}

template <class T>
void Markov_Chain<T>::To_String ()
{
    Markov_State<T>* state;
    Markov_Edge<T>* edge;
    for(auto iterator = m_map.begin(); iterator != m_map.end(); iterator++)
    {
        state = &iterator->second;
        edge = state->edge_list;
        std::cout<<"\nState: " <<  state->data
            <<"\nNum Events: " << state->num_events
            <<"\nNext States: [Frequency / Data]";

        while (edge != NULL)
        {
            std::cout <<"\n\t[" << edge->next_state->data << " / " << edge->event_rate << "]";
            edge = edge->next_edge;
        }

        std::cout << "\n";
    }
}

template <class T>
std::vector<T> Markov_Chain<T>::Output_Random_Sequence (int output_size)
{
    srand (time(NULL));
    std::vector<T> retval;
    int count = 0;
    int val = rand() % m_map.size();
    
    auto item = m_map.begin();
    std::advance( item, val );
    Markov_State<T> state = item->second; 
    Markov_Edge<T>* edge = state.edge_list;

    while (count < output_size && edge != NULL)
    {
        retval.push_back(state.data);
        val = rand() % state.num_events;
        while(val >= 0 && edge->next_edge != NULL)
        {
            val -= edge->event_rate;
            if (val >= 0) edge = edge->next_edge;
        }
        state = *edge->next_state;
        edge = state.edge_list;
        count++;
    }
    return retval;
}

#endif
