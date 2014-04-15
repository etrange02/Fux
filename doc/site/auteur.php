<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel" />
		<meta name="language" content="fr" />
		<meta name="description" content="Page de l'auteur de Fu(X) : David Lecoconnier. Etudiant en 3&egrave;me ann&eacute;e d'informatique &agrave; l'universit&eacute; Paris Descartes." />
		<meta name="keywords" content="Fux, Fu(X), Fux 2.0, fix, fyx, fixplay, fuc, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Auteur</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='auteur.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="description">
					<h3>A propos de l'auteur</h3>
					<p>Salut, moi c'est David alias etrange02 ;) Je suis le cr&eacute;ateur de Fu(X).</p>
					<p>Depuis septembre 2013, je suis &agrave; <a href="http://www.upmc.fr/">l'UPMC</a> (Paris 6) en master informatique (architecture logicielle).</p>
					<p>Mes comp&eacute;tences sont diverses. Je connais un certains nombres de langages que ce soit en programmation ou web (ce site en est la preuve).</p>
					<p>En 2011, j'ai men&eacute; &agrave; la fac un projet de robot suiveur de ligne en lego mindstorm. Le projet est constitu&eacute; de deux programmes Java.
					Vous pourrez trouver toutes les informations sur ce <a href="http://www.ens.math-info.univ-paris5.fr/projets-informatiques/doku.php?id=projets:licence2:2010-2011:gi1:accueil" title="Page du robot suiveur de ligne">lien</a></p>
					<p>Vous pouvez me contacter &agrave; cette adresse fux [at] fuxplay [dot] com.</p>										<p>Sinon, quand j'ai un peu de temps, <a href="http://www.youtube.com/watch?v=C3vrZLPhdbg">je pratique l'aviron</a> !</p>
					
					<h3>A propos de Fu(X)</h3>
					<p>J'ai commenc&eacute; l'&eacute;criture de Fu(X) en 2008, pendant la p&eacute;riode du bac (On ne se refait malheureusement pas). Il &eacute;tait &agrave; ce moment &eacute;crit en langage C.
					Depuis le 24 juillet 2009, j'ai repris l'int&eacute;gralit&eacute; du code afin de le porter en C++. Et par la m&ecirc;me occasion, j'ai am&eacute;lior&eacute; le graphisme du lecteur. Il faut dire qu'il manquait des boutons !
					J'en ai profit&eacute; pour modifier la num&eacute;rotation des versions, d'o&ugrave; le "2.0" dans le nom de Fu(X).
					J'utilise plusieurs biblioth&egrave;ques : wxWidgets, TagLib, FMODex et wxSQLite3 (c'est la petite derni&egrave;re). Fu(X) est pour le moment tr&egrave;s loin d'&ecirc;tre fini. Il manque par exemple l'audioth&egrave;que.</p>
					<p>Voici quelques chiffres pour les curieux : environ 9.484 lignes de code pur, 3.465 lignes de commentaires, 104 fichiers et autant de classes ! Autant dire que &ccedil;a fait beaucoup ;)</p>
					<h3>Remerciements</h3>
					<p>Je tiens &agrave; remercier tr&egrave;s chaleureusement les d&eacute;veloppeurs des diff&eacute;rentes biblioth&egrave;ques utilis&eacute;es, ainsi que plusieurs sites comme <a href="http://www.siteduzero.com/">le site du z&eacute;ro</a> ou encore <a href="http://www.wxdev.fr">wxdev.fr</a> qui m'ont permis de r&eacute;pondre &agrave; bon nombre de questions.</p>
					
					<table id="tableauIcone">
						<tr>
							<td><a class="icone" href="http://www.wxwidgets.org/" title="Site de WxWidgets"><img src="images/wxwidgets.jpg" alt="icone de WxWidgets" /></a></td>
							<td><a class="icone" href="http://www.fmod.org/" title="Site de FMOD"><img src="images/fmod.png" alt="Icone de FMOD" /></a></td>
							<td><a class="icone" href="http://developer.kde.org/~wheeler/taglib.html" title="Site de TagLib"><img src="images/taglib.png" alt="icone de TagLib" /></a></td>
						</tr>
					</table>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>