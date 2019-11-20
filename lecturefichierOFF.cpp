#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstring>
#include "objetsOFF.h"
//#include "objetsOFF.cpp"

using namespace std;

		unsigned long Fbmin;
		unsigned long Fbmax;

		unsigned long Sbmin;
		unsigned long Sbmax;

void* calculNormalface(void * param)
{
	cettestructuremesoulepourquoionpeutpaspasserplusieursargumentsdansunthread * st = (cettestructuremesoulepourquoionpeutpaspasserplusieursargumentsdansunthread*) param;//Création d'un pointeur sur la structure contenant l'objet à utiliser, le numéro de son thread et son tableau de bornes

	point3 pV, ui; //On défini deux variable de type point
	
	double norme;//On défini une variable de type double
	
	for (unsigned long i = st->ranges->at(st->index).at(0); i <= st->ranges->at(st->index).at(1); ++i)//On parcourt le tableau 
	{
		// On définit 3 point3 ou l'on ajoute les valeurs correspondant au 3 sommets de la face visé
		point3 A(st->obj->lpoints[st->obj->lifaces[i].s0]);
		point3 B(st->obj->lpoints[st->obj->lifaces[i].s1]);
		point3 C(st->obj->lpoints[st->obj->lifaces[i].s2]);
		
		// On fait un calcul les vecteurs
		point3 Vab = B - A;
		point3 Vbc = C - B;

		//On calcul la normal de la face
		pV.x = Vab.y * Vbc.z - Vab.z * Vbc.y;
		pV.y = Vab.z * Vbc.x - Vab.x * Vbc.z;
		pV.z = Vab.x * Vbc.y - Vab.y * Vbc.x;

		//std::cout << "Vab - x = " << Vab.x << " y = " << Vab.y << " z = " << Vab.z << std::endl;
		//std::cout << "Vbc - x = " << Vbc.x << " y = " << Vbc.y << " z = " << Vbc.z << std::endl;
		// On calcul la norme
		norme = sqrt(pV.x * pV.x + pV.y * pV.y + pV.z * pV.z);

			//std::cout << "x = " << pV.x << " y = " << pV.y << " z = " << pV.z << std::endl;
			//std::cout << "norme = " << norme << std::endl;

		ui = pV / norme;//On normalise la normal de la face
		//std::cout << ui << "\n";

		// On ajoute cette normal au face au sommet correspondant 
		st->obj->somparfaces[st->obj->lifaces[i].s0].push_back(ui);
		st->obj->somparfaces[st->obj->lifaces[i].s1].push_back(ui);
		st->obj->somparfaces[st->obj->lifaces[i].s2].push_back(ui);

		//std::cout << i << "\n";
		//NormFace.push_back(nface);
	}

	pthread_exit(EXIT_SUCCESS);// On sort du thread
}

void* calculNormalsommet(void * param)
{
	cettestructuremesoulepourquoionpeutpaspasserplusieursargumentsdansunthread * st = (cettestructuremesoulepourquoionpeutpaspasserplusieursargumentsdansunthread*) param;
	
	point3 chibrax; //On défini une variable de type double

	//On parcourt le tableau pour chaque sommet
	for (unsigned long i = st->ranges->at(st->index).at(0); i <= st->ranges->at(st->index).at(1); ++i)
	{
		
		for (unsigned long j = 0; j < st->obj->somparfaces[i].size(); ++j){

			chibrax = chibrax + st->obj->somparfaces[i][j];//On additionne toute les faces d'un sommet
		}
			
		chibrax = chibrax / st->obj->somparfaces[i].size();//On fait la moyenne des faces du sommet se qui nous donne la normal au sommet
		st->obj->NormSommet.at(i) = chibrax;//On ajoute la valeur à notre tableau des normals aux sommets
		
		//std::cout << "[" << X << " ; " << Y << " ; " << Z << "]\n";
	}
		pthread_exit(EXIT_SUCCESS); //On quitte le thread
}



// --------------------------------//
// ------------- MAIN -------------//
//---------------------------------//
int main(int argc, char* argv[])
{
	if(argc != 3 && argc != 4){ //Vérification
		std::cerr << "Wrong usage." << std::endl;
		return -1;
	}

	//Timer 
	 auto start = std::chrono::system_clock::now();
		static const int nbthreads = stoi(argv[2]);
		pthread_t thtab[nbthreads]; // Création d'un tableau de threads de la taille demandée


	Objet monObjet;//On défini une variable de type objet
		monObjet.charge_OFF(argv[1]);//On charge le fichier se qui va nous permettre de mettre dans un tableau les sommets et dans un autre tableau les faces

		unsigned long divFaces = ceil(monObjet.nbfaces / nbthreads);//On divise le nombre de face
		unsigned long divSommets = ceil(monObjet.nbsommets / nbthreads);//On divise le nombre de sommet

		//On défini une variable de type tableau deque pointeur
		std::deque<std::deque<unsigned long>> * st1 = new std::deque<std::deque<unsigned long>>;
		std::deque<std::deque<unsigned long>> * st2 =  new std::deque<std::deque<unsigned long>>;

		//Défini le nombre de thread
		st1->resize(nbthreads);
		st2->resize(nbthreads);


		Objet * ptrObjet = new Objet;//On défini une variable de type objet pointeur

		ptrObjet = &monObjet; // on lui associe l'objet "principal"

		//Division des tableaux en le nombre de threads
		for(int i = 0;i < nbthreads; ++i){

		Fbmin = divFaces*i;
		Fbmax = divFaces*i+divFaces-1;

		Sbmin = divSommets*i;
		Sbmax = divSommets*i+divSommets-1;
		
		//Pour s'arreter à max-1
		if(i == nbthreads-1){
			Fbmax = monObjet.nbfaces - 1;
			Sbmax = monObjet.nbsommets - 1;
		}

		// On rentre ces bornes dans le deque correspondant
		st1->at(i).push_back(Fbmin);
		st1->at(i).push_back(Fbmax);

		st2->at(i).push_back(Sbmin);
		std::cerr << " Bornes st2 : " << Sbmin << " - " << Sbmax << std::endl;
		st2->at(i).push_back(Sbmax);
	}

	for(uint8_t k = 0 ; k < (uint8_t)nbthreads ; ++k){
	
	cettestructuremesoulepourquoionpeutpaspasserplusieursargumentsdansunthread * param = new cettestructuremesoulepourquoionpeutpaspasserplusieursargumentsdansunthread{k, st1, ptrObjet};// Initialisation de la structure avec les paramètres nécéssaires
		pthread_create(&thtab[k], NULL, calculNormalface, (void*) param);//Création des threads
	}
		//monObjet.calculNormalface();
	std::cerr << "All threads started." << std::endl;

	for(int k = 0 ; k < nbthreads ; ++k){
		pthread_join(thtab[k], NULL);
	}

	std::cerr << "All threads joined." << std::endl;
	/* Normales aux faces calculées
	// A voir si on peut utiliser 2 fois le meme pthread_t VVVV /!\ */

	for(uint8_t k = 0 ; k < (uint8_t)nbthreads ; ++k){
		cettestructuremesoulepourquoionpeutpaspasserplusieursargumentsdansunthread * param = new cettestructuremesoulepourquoionpeutpaspasserplusieursargumentsdansunthread{k, st2, ptrObjet}; // On recommence l'opération avec le tableau de bornes des sommets
		pthread_create(&thtab[k], NULL, calculNormalsommet, (void*) param);
	}
		//monObjet.calculNormalsommet();
		std::cerr << "All seconds threads started." << std::endl;	

	for(int k = 0 ; k < nbthreads ; ++k){
		pthread_join(thtab[k], NULL);
	}	
	// Normales aux sommets calculées
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> tpsEcoule = end-start;

    std::cerr << "Temps écoulé : " << tpsEcoule.count() << "s" << std::endl;
    std::cout << tpsEcoule.count() << std::endl;

    if(argc == 4 && argv[3] == "-o"){
    	ifstream statsIn("Stats", ios::binary);
    	ofstream statsOut("Stats", ios::binary);



		//monObjet.infoNormS();
    }

	return(EXIT_SUCCESS);

}
