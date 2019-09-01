/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:09:38 by vlegros           #+#    #+#             */
/*   Updated: 2019/09/01 17:09:38 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DINIC_H
#define DINIC_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <stack>
# define INF 1000000
using namespace std;

typedef struct s_link
{
    string  name;
    int     direction;
    int     flow;
    int     index;
}               t_link;

typedef struct s_node{
    string  name;
    int     level;
    vector<t_link> links;
    int     used;
    int     parent;
}               t_node;

typedef struct s_farm {
    int             ant_num;
    vector<t_node> nodes;
    size_t start;
    size_t  end;
    int     fixed;
}              t_farm;

t_farm    *parse();
int     dinic(t_farm *farm);

#endif