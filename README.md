Configuració de la base de dades:
En el fitxer configuracio.env hem posat el següent:
DB_USER=inep14
DB_PASS=eeCheeJ8ohgh3u
DB_NAME=inep14
DB_HOST=10.5.157.58
Per generar els arxius ODB hem utilitzat aquesta comanda, canviant les rutes segons on tenia cadascú instalat les coses.
odb -I C:\Users\Jordi\Desktop\obd\include -I C:\Users\Jordi\Downloads\boost_1_90_0\boost_1_90_0 --std c++11 -d mysql --generate-query --generate-session --default-pointer std::shared_ptr --profile boost/date-time CapaDeDomini/Model/Usuari.hxx

Una vegada generats, s’han de moure a la carpeta CapaDeDomini/Model i s’han d’afegir al projecte. Els arxius .ixx s’han de configurar com a header, sino ens donava error de compilació.

Després per compilar i executar simplement fer Ctrl + F5.
La ubicació del executable esta a Project1\x64\Debug\Project1.exe
