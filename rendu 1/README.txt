/format : tabs = 4\

Projet  : Propre En Ordre
Auteurs : Axel Hall - Lucas Michel


||Architecture du programme||

  -> : "est inclus par..."
	**********************************************************************
	* shape -> constantes -> file -> robot     ---v                      *
	*				      		  -> particule ---> simulation -> projet *
	*				      		  messages     ---^                      *
	**********************************************************************

  Remarque : le module "file" s'occupe de la lecture du fichier à la place de "simulation"
		 permettant ainsi de séparer la tâche de lecture/écriture et celle de la gestion
		 de la simulation en temps réel (ou par steps). Ceci offre aussi plus de clarté 
		 quant à la structure du projet.
