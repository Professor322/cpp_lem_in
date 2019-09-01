/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:11:54 by vlegros           #+#    #+#             */
/*   Updated: 2019/09/01 17:11:54 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinic.h"


void get_node(t_farm *farm, string buff)
{
    t_node in_node;
    t_node out_node;
    string name = buff.substr(0, buff.find_first_of(' '));

    in_node.name = "L"+ name;
    in_node.level = 0;
    in_node.links.push_back({name, 1, 0, (const int)farm->nodes.size() + 1});
    out_node.name = name;
    out_node.level = 0;
    out_node.links.push_back({in_node.name, 0, 0, (const int)farm->nodes.size()} );
    farm->nodes.push_back(in_node);
    farm->nodes.push_back(out_node);
}

void get_link(t_farm *farm, string buff)
{
    string name1 = buff.substr(0, buff.find('-'));
    string name2 = buff.substr(buff.find('-') + 1);
    vector<t_node>::iterator it1 = find_if(farm->nodes.begin(), farm->nodes.end(), [name1](t_node node){return node.name == name1;});
    vector<t_node>::iterator it2 = find_if(farm->nodes.begin(), farm->nodes.end(), [name2](t_node node){return node.name == name2;});
    t_link link;

    if (it1 - farm->nodes.begin() == farm->start || it2 - farm->nodes.begin() == farm->start)
    {
        if (it1 - farm->nodes.begin() == farm->start)
            it1->links.push_back({"L" + name2, 0, 0, (const int)(it2 - farm->nodes.begin() - 1)});
        else
            it2->links.push_back({"L" + name1, 0, 0, (const int)(it1 - farm->nodes.begin() - 1)});
    }
    else if (it1 - farm->nodes.begin() == farm->end || it2 - farm->nodes.begin() == farm->end)
    {
        if (it1 - farm->nodes.begin() == farm->end)
            it2->links.push_back({name1, 0, 0, (const int)farm->end});
        else
            it1->links.push_back({name2, 0, 0, (const int)farm->end});
    }
    else
    {
        it1->links.push_back({"L" + name2, 0, 0, (const int)(it2 - farm->nodes.begin() - 1)});
        it2->links.push_back({"L" + name1, 0, 0, (const int)(it1 - farm->nodes.begin() - 1)});
    }
}

void get_start_finish(t_farm *farm, string buff, int flag)
{
    getline(cin, buff);
    vector<t_node>::iterator it;
    string name = buff.substr(0, buff.find_first_of(' '));
    farm->nodes.push_back({name, 0});
    if (flag == 1)
        farm->start = farm->nodes.size() - 1;
    else if (flag == 0)
        farm->end = farm->nodes.size() - 1;
}

t_farm    *parse()
{
    t_farm *farm = new t_farm;
    string buff;

    farm->ant_num = -1;
    while(getline(cin, buff))
    {
        if (farm->ant_num == -1)
        {
            farm->ant_num = stoi(buff);
            continue;
        }
        if (buff[0] == '#')
        {
            if (buff.find("##start") != string::npos)
                get_start_finish(farm, buff, 1);
            else if (buff.find("##end") != string::npos)
                get_start_finish(farm, buff, 0);
        }
        else if (buff.find('-') != string::npos)
            get_link(farm, buff);
        else
            get_node(farm, buff);
    }
    return farm;
}