#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
 
int main()
{
    char path_home[PATH_MAX];
    char path[PATH_MAX];
    getcwd(path_home, sizeof(path_home));
    char prev_path[PATH_MAX];
    char current_path[PATH_MAX];
    char cd_path[PATH_MAX];
 
    while(1){
 
        //Znak zachety
 
        getcwd(path, sizeof(path));
        printf("%s~$ ", path);
 
        //Pobieranie aktualnej lokalizacji
 
        getcwd(current_path, sizeof(current_path));
 
        //Pobieranie polecenia
 
        char polecenie[255];
        scanf(" %[^\n]",polecenie);
 
        //Wyjście
 
        if((strncmp(polecenie, "exit",4))==0)
        {
 
            if(strncmp(polecenie,"exit ",5)==0)
            {
                if((strcmp(strstr(polecenie,"-"),"-u"))==0)
                {
                    exit(1);
                }
                else
                {
                 printf("Ta funkcja nie przyjmuje takiego argumentu!/n");
                }
            }
 
            else
            {
                exit(0);
            }
        }
 
        //Zmiana lokalizacji
 
        else if((strncmp(polecenie, "cd",2))==0){
 
           //Zmiana lokalizacji na katalog główny
 
            if(strcmp(polecenie,"cd")==0)
            {
                chdir(path_home);
            }
 
            //Powrót do poprzedniego katalogu
 
            else if(strncmp("cd -",polecenie,4)==0)
            {
                if (chdir(prev_path)!= 0)
                {
                   perror("Error");
                }
 
                chdir(prev_path);
            }
 
            else{
 
                int j = sizeof polecenie;
 
                for(int i=0;i<=j-3;i++)
                {
                    polecenie[i]=polecenie[i+3];
                }
 
                //Zmiana lokalizacji poprzez wpisanie ścieżki bezwzględnej
 
                if(strncmp(polecenie,"/",1)==0)
                {
                    if (chdir(polecenie)!=0)
                    {
                       perror("Error");
                    }
 
                    chdir(polecenie);
                }
 
                //Zmiana lokalizacji poprzez wpisanie ścieżki względnej
 
                else
                {
                    char* strcat(char* path, const char* polecenie);
 
                    if (chdir(polecenie)!=0)
                    {
                       perror("Error");
                    }
 
                    chdir(polecenie);
 
                }
            }
 
            //Przypisywanie do zmiennej prev_path poprzedniej lokalizacji
 
            if(strncmp(current_path,cd_path, sizeof current_path)!=0)
            {
                strcpy(prev_path, current_path);
            }
        }
 
        //Tworzenie pliku
 
        else if((strncmp(polecenie,"touch",5))==0)
        {
 
            int j = sizeof polecenie;
 
            for(int i=0;i<=j-6;i++)
            {
                polecenie[i]=polecenie[i+6];
            }
 
            FILE* file;
            file=fopen(polecenie,"w");
            fclose(file);
        }
 
        //Usuwanie pliku
 
        else if((strncmp(polecenie,"rm",2))==0)
        {
 
            int j = sizeof polecenie;
 
            for(int i=0;i<=j-3;i++)
            {
                polecenie[i]=polecenie[i+3];
            }
 
            if (remove(polecenie)!= 0)
            {
                perror("Error");
            }
 
            remove(polecenie);
        }
 
        //Wyświetlanie pomocy
 
        else if((strcmp(polecenie, "help"))==0)
        {
            printf("####################################\n\n");
            printf("Shell\n");
            printf("\n");
            printf("Autor: Jakub Zuklinski\n");
            printf("\n");
            printf("Polecenia:\n");
            printf("help - pomoc\n");
            printf("exit - wyjscie\n");
            printf("exit -u - wyjscie zakonczone niepowodzeniem\n");
            printf("touch - tworzenie pliku\n");
            printf("rm - usuwanie pliku\n");
            printf("echo - wypisuje ciag znakow podany jako argument\n");
            printf("pwd - wypisuje aktualna lokalizacje uzytkownika\n");
            printf("cd - zmiana katalogu\n");
            printf("Dostepne argumenty polecenia cd:\n");
            printf("cd - - powrot do poprzedniego katalogu\n");
            printf("cd .. - przejscie do katalogu nadrzednego\n");
            printf("cd - przejscie katalogu glownego\n");
            printf("Mozna podac takze lokalizacje wzgledna lub bezwzgledna\n\n");
            
        }
 
        else if((strncmp(polecenie, "echo",4))==0)
        {
            int j = sizeof polecenie;
 
            for(int i=0;i<=j-5;i++)
            {
                polecenie[i]=polecenie[i+5];
            }
 
            printf("%s\n",polecenie);
        }
 
        else if((strncmp(polecenie, "pwd",3))==0)
        {
            printf("Twoja aktualna lokalizacja to: %s\n",current_path);
        }
 
        else
        {
            printf("Bledne polecenie!\n");
        }
    }
 
    return 0;
}
