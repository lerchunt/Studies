#
# réseau pour tp3
# m billaud, 24/11/2013
#

case "$1" in
"-base" )  hasWifi=false ; hasOtherBox=false;;
"-wifi" )  hasWifi=true  ; hasOtherBox=false;;
"-fai" )   hasWifi=true  ; hasOtherBox=true;;
*) 
   echo "usage: $0 {-base|-wifi|-fai}"
   exit 1
   ;;
esac

shift

DISTRIB=slackware
. /net/opt/UML-TOOLS/conf/net-functions.conf
# net-functions.conf

# -------------------------------------------

SWITCH reseau_maison
SWITCH reseau_fai
SWITCH reseau_wifi

#    machine    eth0          eth1
#    ---------  ------------- ----------
HOST tp3boite   reseau_maison reseau_fai
HOST tp3console reseau_maison 

HOST tp3ordinateur reseau_maison reseau_wifi

if [ $hasWifi = true ] ; then
   HOST tp3tablette   reseau_wifi
fi

if [ $hasOtherBox = true ] ; then
   SWITCH reseau_autre_abonne
   HOST  tp3sortie     reseau_fai
   HOST  tp3autreboite reseau_autre_abonne reseau_fai 
fi

RUN
echo "[]"
exit
