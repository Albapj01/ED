/**
 * @file prim_algorithm.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <exception>
#include <utility>
#include <list>
#include <limits>
#include <memory>
#include <valarray>
#include <vector>

#include "wgraph.hpp"

/**
 * @brief Execute the Prim algorithm.
 * The Prim's algorithm create the minimum spannig tree on an undirected
 * weighted graph.
 * @arg[in] g is the graph.
 * @arg[out] mst is the list of edges of g that forms the minium spanning tree.
 * @return the total weigth of the mininum spanning tree. 
 * @pre g->hash_current()
 * @throw std::runtime_error("It is a unconnected graph.") if the input graph
 *        is an unconnected one.
 */
template <class T>
float
prim_algorithm(typename WGraph<T>::Ref g,
               std::vector<typename WGraph<T>::EdgeRef>& mst) noexcept(false)
{
    assert(g->has_current_node());
    float total_distance = 0.0;
    mst.resize(0);

    //TODO
    //Remenber: Use three auxiliary vectors A, V and C.
    //Hint: use std::numeric_limits<float> template to represent "infinite".
    std::vector<bool>U;
    std::vector<int>V;
    std::vector<float>C;

    auto u = g->current_node();

    for(size_t i = 0; i < g->size(); i++)
    {
        if(u->label() == i)
        {
            U.push_back(true);
            V.push_back(-1);
        }
        else
        {
            U.push_back(false);
            V.push_back(u->label());
        }

        C.push_back(g->weight(g->node(i),u)); //coste
    }

    size_t pos_min = 0; 
    float min = C[0];
    for(size_t i =0; i<g->size(); i++) //buscamos el de mas pequeño coste
    {
        if(U[i]==false and C[i]<min)
        {
            pos_min = i;
            min = C[i];
        }
    }
    
    U[pos_min] = true; //seleccionamos el de menor coste

    mst.push_back(g->edge(g->node(pos_min),g->node(V[pos_min]))); //meto dentro de mst el lado en el orden en el cual lo vas metiendo

    total_distance += C[pos_min]; //coste minimo 

    C[pos_min] = std::numeric_limits<float>::infinity(); //ponemos a infinito el coste seleccionado de menor coste para no seleccionarlo nunca mas como minimo

    for (size_t i=1; i<g->size()-1; ++i) //ponemos -1 porque seleccionas n-1 lados que es lo que tiene el grafo de n nodos, aqui buscamos si con el nuevo nodo seleccinado se puede actualizar el coste de alguno en comparacion al nodo que ha seleccionaod anterirormente
    {
        size_t last = pos_min;
        for(size_t i = 0; i<g->size(); i++)
        {
            if(U[i]==false and last!=i and g->weight(g->node(last),g->node(i)) < C[i])
            {
                V[i] = last;
                C[i] = g->weight(g->node(last),g->node(i));
            }
        }

        pos_min = 0;
        min = C[0];

        for(size_t i =0; i<g->size(); i++) //cogemos el siguiente de menor coste para el lado abarcador
        {
            if(U[i]==false and C[i]<min)
            {
                pos_min = i;
                min = C[i];
            }
        }

        if(min == std::numeric_limits<float>::infinity())
            throw std::runtime_error("It is a non-connected graph.");

        g->goto_edge(g->node(pos_min),g->node(V[pos_min]));

        if (!g->has_current_edge() /*Replace with you condition*/)
            throw std::runtime_error("It is a non-connected graph.");

        U[pos_min] = true;

        mst.push_back(g->edge(g->node(pos_min),g->node(V[pos_min])));

        total_distance += C[pos_min];

        C[pos_min] = std::numeric_limits<float>::infinity();  
    }
    //
    return total_distance;
}
