/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 19:51:49 by vlegros           #+#    #+#             */
/*   Updated: 2019/09/01 19:51:49 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinic.h"

void    set_values(vector<t_node> &v, int flag)
{
    for (auto & it : v)
    {
        if (flag)
            it.level = INF;
        it.used = 0;
    }
}

int     bfs(t_farm *farm)
{
    queue <int> q;
    static bool flag = false;

    set_values(farm->nodes, 1);
    farm->nodes[farm->start].level = 0;
    farm->nodes[farm->start].used = 1;
    farm->nodes[farm->end].level = -1;
    q.push((int)farm->start);
    while (!q.empty())
    {
       int temp_node = q.front();
       q.pop();
       for (auto it = farm->nodes[temp_node].links.begin(); it !=  farm->nodes[temp_node].links.end(); it++)
       {
           if (farm->nodes[it->index].used == 0 && it->flow != 1)
           {
               q.push(it->index);
               farm->nodes[it->index].used = 1;
               farm->nodes[it->index].level = farm->nodes[temp_node].level + 1;
           }
       }
    }
    farm->fixed = farm->nodes[farm->end].level;
    return farm->nodes[farm->end].level != -1;
}

void    add_path(t_farm *farm)
{
    int node;
    int child;
    int parent;
    vector<t_link>::iterator child_link_to_parent;
    vector<t_link>::iterator parent_link_to_child;

    node = farm->end;
    while (node != farm->start)
    {
        child = node;
        parent = farm->nodes[child].parent;
        child_link_to_parent = find_if(farm->nodes[child].links.begin(), farm->nodes[child].links.end(), [parent](t_link link){return link.index == parent;});
        parent_link_to_child = find_if(farm->nodes[parent].links.begin(), farm->nodes[parent].links.end(), [child](t_link link){return link.index == child;});
        if (child == farm->end)
        {
                t_link link;
                link.direction = 0;
                link.flow = 1;
                link.index = parent;
                link.name = farm->nodes[parent].name;
                farm->nodes[child].links.push_back(link);
        }
        else if (child_link_to_parent->name != farm->nodes[parent].name)
        {
            t_link link;
            link.direction = 0;
            link.flow = -1;
            link.index = parent;
            link.name = farm->nodes[parent].name;
            farm->nodes[child].links.push_back(link);
        }
        else
        {
          child_link_to_parent->flow = -1;
          child_link_to_parent->direction = 0;
        }
        parent_link_to_child->flow = 1;
       // cout<<node<<"->";
        node = farm->nodes[node].parent;
    }
    //cout<<endl;
}

int     dfs(t_farm *farm)
{
    stack <int> s;

    set_values(farm->nodes, 0);
    s.push(farm->start);
    farm->nodes[farm->start].used = 1;
    while (!s.empty())
    {
        int temp_node = s.top();
        s.pop();
        if (temp_node == farm->end)
        {
            add_path(farm);
            return 1;
        }
        for (auto it = farm->nodes[temp_node].links.begin(); it != farm->nodes[temp_node].links.end(); it++)
        {
            if (farm->nodes[it->index].used == 0 && it->flow != 1 && farm->nodes[it->index].level <= farm->fixed && farm->nodes[it->index].level == farm->nodes[temp_node].level + 1)
            {
                farm->nodes[it->index].used = 1;
                farm->nodes[it->index].parent = temp_node;
                s.push(it->index);
            }
        }
    }
    return 0;
}

int     dinic(t_farm *farm)
{
    int     max_flow = 0;
    int flow = 0;

 //   bfs(farm);
   // dfs(farm);
    while (bfs(farm))
    {
        flow = dfs(farm);
        while (flow) {
            max_flow += flow;
            flow = dfs(farm);
        }
    }
    return max_flow;
}