/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:08:51 by vlegros           #+#    #+#             */
/*   Updated: 2019/09/01 17:08:51 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinic.h"

void    debug(t_farm *farm)
{
    cout<<"start: "<<farm->start<<endl;
    cout<<"finish: "<<farm->end<<endl;
    int i = 0;
    for (auto & node : farm->nodes)
    {
        cout<<"|"<<setw(5)<<i++<<"|"<<"level: "<<node.level<<setw(10)<<node.name<<"|"<<"->";
        for (auto & link : node.links)
            cout<<"|name: "<<setw(3)<<link.name<<" direction: "<<link.direction<<" flow: "<<link.flow<<" index: "<<link.index<<"|->";
        cout<<endl;
    }
}

int     main()
{
    t_farm *farm;

    farm = parse();
    cout<<"max flow: "<<dinic(farm)<<endl;
    //debug(farm);
    return 0;
}