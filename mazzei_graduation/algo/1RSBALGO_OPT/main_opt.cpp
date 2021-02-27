#include "defines.h"

int main(){

    //random seed for randStream
    srand(1);

    //initialize variables
    myPopulation Pop;
    Pop.time = 0;


    while(Pop.time<MAX_TIME){

        //choose site & bonds
        Pop.currSiteIdx = Pop.time%Nh;

        //choose 2K + 2 sites
        Pop.choose_sites();

        //foreach cluster
        for(int cc = 0; cc<Nc ; cc++){

            Pop.currClusterIdx = cc;
            Pop.currCluster = &Pop.Cluster[cc];

            //generate free energies
            //& merge fields
            Pop.currCluster->
                    merge_fields_opt(Pop.J,Pop.NeighIdx);

            //reweigh result & update
            Pop.currCluster->
                    reweigh_fields_opt(Pop.currSiteIdx);

        }

        //evaluate site contributions
        Pop.evaluate_site();

        Pop.time++;
        if(Pop.time%2000==0){
            cout<<"sim time: "<<Pop.time<<endl;

        }
        if((Pop.time)%2000==0){
            Pop.write_file();

        }
    }
    //sim ended
    return 0;
}


