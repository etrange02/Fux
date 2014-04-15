<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel" />
		<meta name="language" content="fr" />
		<meta name="description" content="Projets de licence 3 de l'universit&eacute; Paries Descartes" />
		<meta name="keywords" content="Fux, Fu(X), Fux 2.0, fix, fyx, fixplay, fuc, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Projet Licence 3 informatique</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="stylesheet" type="text/css" href="./Styles/style_projet.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='projet.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="projet">
					<h3>Projets universitaires de L3 Paris Descartes</h3>
					<p>Il existe parfois des projets qui méritent d'être diffusés sur le net. Il ne faut pas nécessairement être en master ou en école d'ingénieur pour faire un bon travail. En voici la preuve !</p>
					<p><a href="#phoneandrescue" title="Projet">Phone&amp;Rescue</a><br />
						<a href="#quoridor" title="Jeu de labirynthe">Quoridor</a><br />
						<a href="#tetris" title="Jeu du célèbre Tétris mais à 2 joueurs...">Tetris</a><br />
						<a href="#hiver" title="Reprise du 1er mouvement de l'Hiver de Vivaldi">Vivaldi - Hiver</a><br />
					<br /><br /><br /></p>
					
					<h3 id="phoneandrescue">Phone&amp;Rescue</h3>
					<h4>Qu'est-ce que Phone&Rescue ?</h4>
					<p>L’Imagine Cup est une compétition organisée par Microsoft pour les étudiants. Il s’agit de créer des applications et d’imaginer des solutions qui peuvent aider à rendre le monde meilleur. La compétition tourne autour des problèmes du millénaire à savoir la pauvreté, la faim, l’inégalité des sexes, l’environnement, l’accès à l’éducation, et la santé.<br />
					Dans cette optique, nous avons eu trois différentes idées. Cependant dans le cadre de notre projet de fin de licence nous avons finalement décidé de travailler sur le projet Windows Phone.<br />
					La problématique que nous essayons de résoudre est : comment réduire le temps d’intervention des secoures sur les lieux d’un accident ? En effet, il faut environ 16 minutes pour que ces derniers arrivent sur les lieux d’un accident. C’est dans l’optique de réduire ce délai que nous avons créé Phone&Rescue.<br />
					Phone&Rescue est une application pour Smartphone qui implique toutes les personnes de la chaîne de secours ; de l’appelant au médecin en passant par l’opérateur. L’application ne prend pas de décision mais apporte une aide significative pour réduire le temps d’intervention des secours.<br />
					</p>
					<h4>Démonstration</h4>
					<p><iframe width="420" height="315" src="http://www.youtube.com/embed/t23vuNS9igo" frameborder="0" allowfullscreen></iframe></p>
					<p>Les différents programmes sont faits en C# ou C++. Réalisé par <a title="julien.bernard@etu.parisdescartes.fr" href="mailto:julien.bernard@etu.parisdescartes.fr">Julien Bernard</a>, <a title="ludovicdaniel@hotmail.fr" href="mailto:ludovicdaniel@hotmail.fr">Ludovic Daniel</a>, <a title="fux@fuxplay.com" href="mailto:fux@fuxplay.com">David Lecoconnier</a> et <a title="idir.mez@gmail.com" href="mailto:idir.mez@gmail.com">Idir Meziani</a>.<br /><img src="./images/photo_groupe.jpg" title="Equipe de Phone&Rescue"/>
					<br /><br /><br /><br /></p>
					
					<h3 id="quoridor">Quoridor</h3>
					<h4>Qu'est-ce que Quoridor ?</h4>
					<p>Quoridor est un jeu de société dont le but est d'atteindre en premier l'autre côté du plateau. Pour vous aidez, vous disposez de 10 murs que vous pouvez placer comme bon vous semble.<br />
					Attention : ne vous bloquez pas !
					</p>
					<p>Réalisé en Java par <a title="fux@fuxplay.com" href="mailto:fux@fuxplay.com">David Lecoconnier</a>, <a title="a.leneveu@live.fr" href="mailto:a.leneveu@live.fr">Alexis Leneveu</a> et <a title="liber.oscar@gmail.com" href="mailto:liber.oscar@gmail.com">Oscar Liber</a>.<br />
						<a href="./projets/Quoridor.zip" title="Vous devez disposer d'une machine virtuelle Java pour jouer. Vous pourrez la trouver en faisant une recherche sur le net. Décompressez le fichier et lancez le fichier Quoridor.jar">Télécharger le jeu</a>
					<br /><br /><br /><br /></p>
					
					<h3 id="tetris">Tetris</h3>
					<h4>Qu'est-ce que ce Tetris ?</h4>
					<p>Le Tétris, tout le monde connait ? Eh bien non ! Avec cette version, votre but sera de battre l'ordinateur. Et, oui, c'est une version à 2 joueurs !</p>
					<p>Réalisé en Java par <a title="julien.bernard@etu.parisdescartes.fr" href="mailto:julien.bernard@etu.parisdescartes.fr">Julien Bernard</a> et <a title="adrien.zamant@etu.parisdescartes.fr" href="mailto:adrien.zamant@etu.parisdescartes.fr">Adrien Zamant</a>.<br />
						<a href="./projets/Tetris.zip" title="Vous devez disposer d'une machine virtuelle Java pour jouer. Vous pourrez la trouver en faisant une recherche sur le net.">Télécharger le jeu</a>
					<br /><br /><br /><br /></p>
					
					<h3 id="hiver">Vivaldi - Hiver</h3>
					<h4>Qu'est-ce que c'est ?</h4>
					<p>Qui disait que le classique c'est pour les nuls ? Avec cette version revue et corrigée, Vivaldi se met au goût du jour !</p>
					<p><iframe width="420" height="315" src="http://www.youtube.com/embed/agqGP5VR5e8" frameborder="0" allowfullscreen></iframe><br />
					Réalisé avec CSound par <a title="fux@fuxplay.com" href="mailto:fux@fuxplay.com">David Lecoconnier</a>.</p>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>