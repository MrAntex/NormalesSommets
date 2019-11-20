#include <errno.h>
#include <unistd.h>

#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <cmath>

#include <iostream>

#include "objetsOFF.h"

/*
point3 VecteurFromPoints(const point3 * _p1, const point3 * _p2) {
point3 res;
	res.x = _p2->x - _p1->x;
	res.y = _p2->y - _p1->y;
	res.z = _p2->z - _p1->z;
return res;
}*/

Objet::Objet() {
	strcpy(nom, "nil");
	nbsommets=0;
	nbfaces=0;
	id=0;
}

Objet::~Objet() {
//nil
}
///////////////////////////////cm




void Objet::infoNormF()
{
	std::cout << "\n NORMAL AUX FACES\n";
	//Boucle qui parcourt tout le tableau des somparfaces
	for (unsigned long i = 0; i < somparfaces.size(); ++i)
	{
		for (unsigned long j = 0; j < somparfaces[i].size(); ++j)
		{
			std::cout << i << " " << j << "[" << somparfaces[i][j].x << " ; " << somparfaces[i][j].y << " ; " << somparfaces[i][j].z << "]\n";// On écrit alors touts les élémants du tableau dans l'ordre
		}
		std::cout << i <<"////////////////////// \n";
	}
}

void Objet::infoNormS()
{
	std::cout << "\n NORMAL AUX SOMMETS\n";
	// Boucle qui parcourt tout le tableau des NormSommet
	for (unsigned long i = 0; i < NormSommet.size(); ++i)
	{
		// Affiche toutes les normals aux sommets qu'on a calculé
		std::cout << i << " : [" << NormSommet[i].x << " ; " << NormSommet[i].y << " ; " << NormSommet[i].z << "]\n";
	}
}


/////////////////////////////

void Objet::charge_OFF(const char nom_fichier[40])
{

unsigned int i;
FILE * fichier;
unsigned int n;

char magic[10];

if ((fichier=fopen(nom_fichier,"r"))==NULL)
        {
		perror("Erreur a l'ouverture du fichier OFF");
        	exit(1);
        }

fscanf(fichier,"%s\n",magic);

if (strcmp(magic, "OFF")!=0) {
	perror("Erreur dans l'en tête du fichier OFF");
        exit(0);
}

fscanf(fichier,"%u %u %u\n",&nbsommets, &nbfaces, &i);


///////////////////////////////
somparfaces.resize(nbsommets);
NormSommet.resize(nbsommets);
///////////////////////////////https://www.google.com/search?q=open+a+shared+repo+on+gitkraken&ie=utf-8&oe=utf-8&client=firefox-b-e

//Remplissage de la liste de points
point3 temp;

for (i=0;i<nbsommets;i++)
{
    fscanf(fichier,"%Lf %Lf %Lf L\n",&temp.x,&temp.y,&temp.z);
	if (min.x>temp.x)
		min.x=temp.x;
	if (min.y>temp.y)
		min.y=temp.y;
	if (min.z>temp.z)
		min.z=temp.z;

	if (max.x<temp.x)
		max.x=temp.x;
	if (max.y<temp.y)
		max.y=temp.y;
	if (max.z<temp.z)
		max.z=temp.z;

	lpoints.push_back(temp);

	/////////////////
	//Ajout du nombre de case max (qui correspond au nombre de sommets)
	//somparfaces.push_back(std::deque<point3>());
	////////////////

}


//Remplissage de la liste de faces
iFaceTri ftemp;

for (i=0;i<nbfaces;i++)
{
   fscanf(fichier,"%u %u %u %u\n",&n, &ftemp.s0, &ftemp.s1,&ftemp.s2);
	if (n!=3) {
		perror("Erreur au chargement des faces, non triangulaires");
		exit(1);
		}
	lifaces.push_back(ftemp);
}


//calcul du centroid de l'objet à partir de la boîte min/max
centroid.x = (max.x + min.x) / 2.0f;
centroid.y = (max.y + min.y) / 2.0f;
centroid.z = (max.z + min.z) / 2.0f;

std::cerr << "Chargement du fichier " << nom_fichier << std::endl;
std::cerr << "\t" << nom_fichier << " : " << nbsommets << " points - " << nbfaces << " faces" << std::endl;
std::cerr << "\t" << nom_fichier << " MAX : " << max.x << " " << max.y << " " << max.z << std::endl;
std::cerr << "\t" << nom_fichier << " MIN : " << min.x << " " << min.y << " " << min.z << std::endl;
std::cerr << "\t" << nom_fichier << " CENTROID : " << centroid.x << " " << centroid.y << " " << centroid.z << std::endl;
//std::cerr << "type nbfaces : " << type_name<decltype(nbfaces)>() << " - nbsommets : " << type_name<decltype(nbsommets)>() << std::endl;
fclose(fichier);
}


void Objet::infos()
{
   std::cerr << "Objet " << nom << ", nbsommets " << nbsommets << " nbfaces " << nbfaces << "\n";

	std::cerr << "\n SOMMETS\n";
	std::deque<point3>::iterator pit, pitend = lpoints.end();

	for( pit = lpoints.begin(); pit != pitend; ++pit)
		std::cerr << "[" << (*pit).x << " " << (*pit).y << " " << (*pit).z << "]\n";

	std::cerr << "\n FACES\n";
	std::deque<iFaceTri>::iterator fit, fitend = lifaces.end();

	for(fit = lifaces.begin() ; fit != fitend ; ++fit)
		std::cerr << "{" << (*fit).s0 << " " << (*fit).s1 << " " << (*fit).s2 << "}\n";
}
