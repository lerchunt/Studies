#
# Configuration des machines alpha beta gamma
#

# a lancer depuis les  machines virtuelles


if [ $# != 1 ]
then 
  echo "Usage : $0 {alpha,beta,gamma}"
  exit 0
fi

machine=$1
utilisateur=u${machine}
motdepasse=${machine}123

useradd -m $utilisateur
echo $utilisateur:$motdepasse | chpasswd


echo $machine.example.net > /etc/HOSTNAME

cat > /etc/hosts <<EOF

127.0.0.1       $machine.example.net $machine
       
192.168.10.1    alpha.example.net  alpha
192.168.10.2    beta.example.net   beta
192.168.10.3    gamma.example.net  gamma
EOF

