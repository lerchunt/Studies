<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" >
<head>
	<meta http-equiv="content-type" content="text/html; charset=utf-8" />
	<meta name="author" content="root"/>
	<meta name="keywords" content="configuration, client" />
	<meta name="description" content="Script php affichant la configuration du client" />
	<meta name="robots" content="all" />
	<title>Votre configuration</title>
	<style type="text/css" media="all">
		@import "style.css";
	</style>
</head>
<body>
<h1>Noble visiteur, voici nos informations à votre sujet!</h1>

<div id="container">

	<div id="intro">
		<div id="quickSummary">
			<p class="p1"><span>Nos services de renseignements sont extrèmement performants</span></p>
			<p class="p2"><span>... et ceci n'est qu'un aperçu de ce que nous savons sur vous...</span></p>
		</div>	
	</div>

	<div id="supportingText">
		<div id="preamble">

			<p class="p1"><span>Par le passé, les nains du royaume des petits géants ont usé de moulte déguisement pour essayer d'infiltrer notre peuple. Ils ont toujours échoué: pour déjouer leurs vaines tentatives, nous avons développé d'excellents services de renseignements. </span></p>
			<p class="p2"><span>Ceux-ci exploitent les toutes dernières technologiques: reconnaissance morphologique d'un nain du petit royaume assistée par intelligence artificielle basée sur des réseaux neuronaux, analyse systématique des entêtes HTTP circulant sur nos ordinateurs reliés à Internet, etc...</span></p>
			<h3><span>Nos informations</span></h3>
			<ul>
				<li><?php echo "Votre navigateur est : <strong>".$_SERVER["HTTP_USER_AGENT"]."</strong>"; ?></li>
				<li><?php echo "Votre adresse IP est : <strong>".$_SERVER["REMOTE_ADDR"]."</strong>"; ?></li>
				<li><?php echo "Vous avez demandé la page: <strong>".$_SERVER["QUERY_STRING"]."</strong>";?></li>
				<li><?php echo "Vous acceptez les documents de type MIME: <strong>".$_SERVER["HTTP_ACCEPT"]."</strong>";?></li>
			</ul>
		</div>
		
		<div id="footer">
			<a href="http://validator.w3.org/check/referer" title="Check the validity of this site&#8217;s XHTML">xhtml</a> &nbsp; 
			<a href="http://jigsaw.w3.org/css-validator/check/referer" title="Check the validity of this site&#8217;s CSS">css</a> &nbsp; 
		</div>

	</div>

		<div id="linkList">
		<!--extra div for flexibility - this list will probably be the trickiest spot you'll deal with -->
		<div id="linkList2">
			<div id="lselect">
				<h3><span>Navigation</span></h3>
				<!-- list of links begins here. There will be no more than 8 links per page -->
				<ul>
					<li><a href="./index.xhtml">Retour</a> à la page d'accueil</li>
					<li><a href="./intranet/index.xhtml">Accéder</a> à l'intranet</li>
				</ul>
			</div>
		</div>
	</div>
</div>
</body>
</html>

