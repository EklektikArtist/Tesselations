/*
 * Copyright (C) The University of Texas, 2006. All rights reserved.
 * UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING THIS
 * SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR ANY PARTICULAR PURPOSE, NON-INFRINGEMENT
 * AND WARRANTIES OF PERFORMANCE, AND ANY WARRANTY THAT MIGHT OTHERWISE
 * ARISE FROM COURSE OF DEALING OR USAGE OF TRADE. NO WARRANTY IS EITHER
 * EXPRESS OR IMPLIED WITH RESPECT TO THE USE OF THE SOFTWARE OR
 * DOCUMENTATION. Under no circumstances shall University be liable for
 * incidental, special, indirect, direct or consequential damages or loss
 * of profits, interruption of business, or related expenses which may
 * arise from use of Software or Documentation, including but not limited
 * to those resulting from defects in Software and/or Documentation, or
 * loss or inaccuracy of data of any kind.
 */

// Modifications made by David Roberts <d@vidr.cc>, 2010.

#include "cls_population.h"
#include "organism.h"
#include "cls_hub.h"
#include <iostream>

using namespace NEAT;

Population::Population(void) {
	winnergen=0;
	highest_fitness=0.0;
	highest_last_changed=0;
	spawn(NULL,0);
}

Population::Population(Genome *g,int size) {
	winnergen=0;
	highest_fitness=0.0;
	highest_last_changed=0;
	spawn(g,size);
}

bool Population::verify() {
	std::vector<Hub>::iterator curorg;

	bool verification;

	for(curorg=hubs.begin();curorg!=hubs.end();++curorg) {
		verification=((curorg)->gnome).verify();
	}

	return verification;
} 

bool Population::spawn(Genome *g,int size) {
	int count;
	Genome new_genome;
	Hub new_hub;

	//Create size copies of the Genome
	//Start with perturbed linkweights
	for(count=1;count<=size;count++) {
		//cout<<"CREATING ORGANISM "<<count<<endl;

		new_genome=*g->duplicate(count); 
		//new_genome->mutate_link_weights(1.0,1.0,GAUSSIAN);
		new_genome.mutate_link_weights(1.0,1.0,COLDGAUSSIAN);
		new_genome.randomize_traits();
		new_hub=*new Hub(&new_genome);
		hubs.push_back(new_hub);
	}

	//Keep a record of the innovation and node number we are on
	cur_node_id=new_genome.get_last_node_id();
	cur_innov_num=new_genome.get_last_gene_innovnum();

	//Separate the new Population into species
	speciate();

	return true;
}

bool Population::speciate() {
	std::vector<Hub>::iterator curorg;  //For stepping through PopulationJ
	std::vector<Species>::iterator curspecies; //Steps through species
	Hub *comporg;  //Hub for comparison 
	Species newspecies; //For adding a new species

	int counter=0; //Species counter

	//Step through all existing hubs
	for(curorg=hubs.begin();curorg!=hubs.end();++curorg) {

		//For each hub, search for a species it is compatible to
		curspecies=species.begin();
		if (curspecies==species.end()){
			//Create the first species
			newspecies=*new Species(++counter);
			species.push_back(newspecies);
			newspecies.add_Organism((Organism*)*curorg);  //Add the current hub
			curorg->species=newspecies;  //Point hub to its species
		} 
		else {
			comporg=(Hub*)(curspecies)->first();
			while((comporg!=0)&&
				(curspecies!=species.end())) {

					if ((((curorg)->gnome)->compatibility(comporg->gnome))<NEAT::compat_threshold) {

						//Found compatible species, so add this hub to it
						curspecies->add_Organism(curorg);
						curorg.species=(curspecies);  //Point hub to its species
						comporg=0;  //Note the search is over
					}
					else {

						//Keep searching for a matching species
						++curspecies;
						if (curspecies!=species.end()) 
							comporg=(Hub)(*curspecies)->first();
					}
				}

				//If we didn't find a match, create a new species
				if (comporg!=0) {
					newspecies=*new Species(++counter);
					species.push_back(newspecies);
					newspecies.add_Organism(&curorg);  //Add the current hub
					(curorg)->species=*newspecies;  //Point hub to its species
				}

		} //end else 

	} //end for

	last_species=counter;  //Keep track of highest species

	return true;
}

bool Population::print_to_file_by_species(const char *filename) {

  std::vector<Species*>::iterator curspecies;

  std::ofstream outFile(filename,std::ios::out);

  //Make sure it worked
  if (!outFile) {
    std::cerr<<"Can't open "<<filename<<" for output"<<std::endl;
    return false;
  }


  //Step through the Species and print them to the file
  for(curspecies=species.begin();curspecies!=species.end();++curspecies) {
    (*curspecies)->print_to_file(outFile);
  }

  outFile.close();

  return true;

}

bool Population::rank_within_species() {
	std::vector<Species>::iterator curspecies;

	//Add each Species in this generation to the snapshot
	for(curspecies=species.begin();curspecies!=species.end();++curspecies) {
		(*curspecies)->rank();
	}

	return true;
}

void Population::estimate_all_averages() {
	std::vector<Species>::iterator curspecies;

	for(curspecies=species.begin();curspecies!=species.end();++curspecies) {
		(curspecies)->estimate_average();
	}

}

Species *Population::choose_parent_species() {  

	double total_fitness=0;
	std::vector<Species>::iterator curspecies;  
	double marble; //The roulette marble
	double spin; //Spins until the marble reaches its chosen point

	//We can try to keep the number of species constant at this number
	int num_species_target=4;
	int num_species=species.size();
	double compat_mod=0.3;  //Modify compat thresh to control speciation


	//Keeping species diverse
	//This commented out code forces the system to aim for 
	// num_species species at all times, enforcing diversity
	//This tinkers with the compatibility threshold, which
	// normally would be held constant

	//if (num_species<num_species_target)
	//	NEAT::compat_threshold-=compat_mod;
	//else if (num_species>num_species_target)
	//	NEAT::compat_threshold+=compat_mod;

	//if (NEAT::compat_threshold<0.3) NEAT::compat_threshold=0.3;


	//Use the roulette method to choose the species 

	//Sum all the average fitness estimates of the different species
	//for the purposes of the roulette
	for(curspecies=species.begin();curspecies!=species.end();++curspecies) {
		total_fitness+=(*curspecies)->average_est;
	}

	marble=randfloat()*total_fitness;
	curspecies=species.begin();
	spin=(*curspecies)->average_est;
	while(spin<marble) {
		++curspecies;

		//Keep the wheel spinning
		spin+=(*curspecies)->average_est;
	}
	//Finished roulette

	//  cout<<"Chose random species "<<(*curspecies)->id<<endl;
	//printf("Chose random species %d.\n",(*curspecies)->id);

	//Return the chosen species
	return (*curspecies);
}

bool Population::remove_species(Species *spec) {
	std::vector<Species*>::iterator curspec;

	curspec=species.begin();
	while((curspec!=species.end())&&
		((*curspec)!=spec))
		++curspec;

	if (curspec==species.end()) {
		//   cout<<"ALERT: Attempt to remove nonexistent Species from Population"<<endl;
		return false;
	}
	else {
		species.erase(curspec);
		return true;
	}
}

Hub Population::remove_worst() {

	double adjusted_fitness;
	double min_fitness=999999;
	std::vector<Hub>::iterator curorg;
	Hub *org_to_kill = 0;
	std::vector<Hub>::iterator deadorg;
	Species *orgs_species; //The species of the dead hub

	//Make sure the hub is deleted from its species and the population

	//First find the hub with minimum *adjusted* fitness
	for(curorg=hubs.begin();curorg!=hubs.end();++curorg) {
		adjusted_fitness=((*curorg)->fitness)/((*curorg)->species->organisms.size());
		if ((adjusted_fitness<min_fitness)&&
			(((*curorg)->time_alive) >= NEAT::time_alive_minimum))
		{
			min_fitness=adjusted_fitness;
			org_to_kill=(*curorg);
			deadorg=curorg;
			orgs_species=(*curorg)->species;
		}
	}

	if (org_to_kill) {
        remove_org( org_to_kill );
	}

	return org_to_kill;
} 

//KEN: New 2/17/04
//This method takes an Hub and reassigns what Species it belongs to
//It is meant to be used so that we can reasses where Hubs should belong
//as the speciation threshold changes.
void Population::reassign_species(Hub *org) {
	
		Hub *comporg;
		bool found=false;  //Note we don't really need this flag but it
		                    //might be useful if we change how this function works
		std::vector<Species*>::iterator curspecies;
		Species *newspecies;
		Species *orig_species;

		curspecies=(species).begin();

		comporg=(Hub)(*curspecies)->first();
		while((curspecies!=(species).end()) && (!found)) 
		{	
			if (comporg==0) {
				//Keep searching for a matching species
				++curspecies;
				if (curspecies!=(species).end())
					comporg=(Hub)(*curspecies)->first();
			}
			else if (((org->gnome)->compatibility(comporg->gnome))<NEAT::compat_threshold) {
				//If we found the same species it's already in, return 0
				if ((*curspecies)==org->species) {
					found=true;				
					break;
				}
				//Found compatible species
				else {
					switch_species(org,org->species,(*curspecies));
				    found=true;  //Note the search is over
				}
			}
			else {
				//Keep searching for a matching species
				++curspecies;
				if (curspecies!=(species).end()) 
					comporg=(Hub)(*curspecies)->first();
			}
		}

		//If we didn't find a match, create a new species, move the org to
		// that species, check if the old species is empty, 
		//re-estimate averages, and return 0
		if (found==false) {

			//Create a new species for the org
			newspecies=new Species(++(last_species),true);
			(species).push_back(newspecies);
		
			switch_species(org,org->species,newspecies);
		}

}

//Remove the hub from its species and the population
void Population::remove_org(Hub *org_to_kill) {
	
	std::vector<Hub>::iterator deadorg;

	Species *orgs_species; //The species of the dead hub
	orgs_species=(org_to_kill)->species;
	orgs_species->remove_org(org_to_kill);  //Remove from species
	delete org_to_kill;  //Delete the hub itself 
    
	for(deadorg=hubs.begin();deadorg!=hubs.end();++deadorg) {
		if (*deadorg == org_to_kill )
		    {
	        hubs.erase(deadorg); //Remove from population list
            break;
		    }
	    }

	//Did the species become empty?
	if ((orgs_species->organisms.size())==0) {
		remove_species(orgs_species);
		delete orgs_species;
	}
	//If not, re-estimate the species average after removing the hub
	else {
		orgs_species->estimate_average();
	}
}

//Move an Hub from one Species to another
void Population::switch_species(Hub *org, Species *orig_species, Species *new_species) {

		//Remove hub from the species we want to remove it from
		orig_species->remove_org(org);

		//Add the hub to the new species it is being moved to
		new_species->add_Organism(org);
		org->species=new_species;

		//KEN: Delete orig_species if empty, and remove it from pop
		if ((orig_species->organisms.size())==0) {

			remove_species(orig_species);
			delete orig_species;

			//Re-estimate the average of the species that now has a new member
			new_species->estimate_average();
		}
		//If not, re-estimate the species average after removing the hub
		// AND the new species with the new member
		else {
			orig_species->estimate_average();
			new_species->estimate_average();
		}
}
