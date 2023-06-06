/**
 * @file graph_traversals.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <tuple>
#include <stack>
#include <queue>

#include "wgraph.hpp"



/**
 * @brief Depth first scan from a vertex.
 * The current node will be used as start vertex.
 * @arg g is the graph.
 * @arg p is a functional to process a spanning tree edge.
 * @return the last p() return value.
 * @pre g.has_current_node()
 * @warning p must accept the interface
 * bool (std::tuple<typename WGraph<T>::NodeRef,
 *                  typename WGraph<T>::NodeRef>)
 * where a tuple (u, v) means "Reached node u arriving from v".
 * @warning Only a spanning tree rooted in the current node of the graph
 *          will be scanned.
 */
template<class T, class Processor>
bool depth_first_scan(typename WGraph<T>::Ref g, Processor& p) //profundidad
{
    assert(g->has_current_node());
    bool ret_val = true;
    //A tuple (u, v) means "Reached node u arriving from v".
    using Tuple = std::tuple<typename WGraph<T>::NodeRef,
                             typename WGraph<T>::NodeRef>;
    //TODO
    //Remenber: use the alias Tuple because we want to know the edges that
    //          form the spanning tree to.
    //Remenber: the first tuple is (current_node, current_node)

    std::stack< Tuple > s;
    s.push(Tuple(g->current_node(),g->current_node()));
    while(not s.empty())
    {
    	auto tup = s.top();
        auto u = std::get<0>(tup);
    	s.pop();
    	if(not u->is_visited())
    	{
    		u->set_visited(true);
            p(tup);
    		g->goto_node(u);
    		while(g->has_current_edge())
    		{
    			auto v = g->current_edge()->other(u);

    			if(not v->is_visited())
    			{
    				s.push(Tuple(v,u));
    			}
    			g->goto_next_edge();
    		}
    	}
    }

    //
    return ret_val;
}

/**
 * @brief breadth first scan from a vertex.
 * The current node will be used as start node.
 * @arg g is the graph.
 * @arg p is a functional to process a spanning tree edge.
 * @return the last p() return value.
 * @pre g.has_current_node()
 * @warning p must accept the interface
 * bool (std::tuple<typename WGraph<T>::NodeRef,
 *                  typename WGraph<T>::NodeRef>)
 * where a tuple (u, v) means "Reached node u arriving from v".
 * @warning Only a spanning tree rooted in the current node of the graph
 *          will be scanned.
 */
template<class T, class Processor>
bool breadth_first_scan(typename WGraph<T>::Ref g, Processor& p) //anchura
{
    assert(g->has_current_node());
    bool ret_val = true;
    //A tuple (u, v) means "Reached node u arriving from v".
    using Tuple = std::tuple<typename WGraph<T>::NodeRef,
                             typename WGraph<T>::NodeRef>;
    //TODO
    //Remenber: use the alias Tuple because we want to know the edges that
    //          form the spanning tree too.
    //Remenber: the first tuple must be (current_node, current_node)
    std::queue< Tuple > q;
    q.push(Tuple(g->current_node(),g->current_node()));
    while(not q.empty())
    {
    	auto tup = q.front();
        auto u = std::get<0>(tup);
    	q.pop();
    	if(not u->is_visited())
    	{
    		p(tup);
    		u->set_visited(true);
    		g->goto_node(u);
    		while(g->has_current_edge())
    		{
    			auto v = g->current_edge()->other(u);
    			if(not v->is_visited())
    			{
    				q.push(Tuple(v,u));
    			}
    			g->goto_next_edge();
    		}
    	}
    }

    //
    return ret_val;
}

