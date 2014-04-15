<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta name="author" content="Lecoconnier David" />
		<meta name="category" content="Logiciel" />
		<meta name="language" content="fr" />
		<meta name="description" content="Page d'aide et d'explication sur Fu(X). Le logiciel se veut simple et intuitif, et apporte quelques nouveaut&eacute;s !" />
		<meta name="keywords" content="Fux, Fu(X), Fux 2.0, fix, fyx, fixplay, fuc, musique, rapide, simple, lecteur, audio, mp3, m3u, tag, liste, gestion, interface, claire, efficace, explorateur, glisser, d&eacute;poser" />
		<meta name="robots" content="all" />
		<meta http-equiv="content-language" content="french" />
		<meta http-equiv="Content-Type" lang="fr" content="text/html; charset=UTF-8" />
		<title>Fu(X) 2.0 - Aide</title>
		<link rel="stylesheet" type="text/css" href="./Styles/style.css" media="screen" />
		<link rel="icon" type="image/png" href="images/play.png" />
	</head>
	<body>
		<?php
			include("menu.php");
			require("bdd.php");
		?>
		
		<div id="corps">
			<?php $page_actuelle='aide.php'; include("droite.php"); ?>
			<div id="milieu">
				<div id="description">
					<h3>Aide</h3>
					<p>Bonjour, et bienvenue dans la partie aide. Dans cette partie, je vais vous pr&eacute;senter bri&egrave;vement l'utilisation de Fu(X).</p>
					<p>Avant tout, commencez par r&eacute;ccup&eacute;rer la derni&egrave;re version de Fu(X)<br />
					Puis installez-vous confortablement dans votre fauteuil et laissez-vous aller...</p>
					<p>Lors de l'installation, vous pouvez choisir de mettre Fu(X) en lecteur par d&eacute;faut et placer des raccourcis en diff&eacute;rents endroits du bureau.
					Ceux-ci vous permettront un acc&eacute;s direct.<br />
					Maintenant, l'&eacute;tape la plus cruciale de la proc&eacute;dure : lancer Fu(X) !</p>
					<p>Voici un aper&ccedil;u de l'accueil de Fu(X) : </p>
					<p class="image_centre"><a href="images/fux_accueil.jpg" title="L'image est &agrave; taille r&eacute;elle !"><img class="max_size" src="images/fux_accueil.jpg" alt="Accueil de Fu(X)" /></a></p>
					<p>Maintenant, on va mettre de la musique, il faut bien car c'est le but du programme ;). Les possibilit&eacute;s sont multiples :
					</p>
						<ul>
							<li>La mani&egrave;re la plus classique qui puisse exister, aller dans Fichier puis Ouvrir. Un explorateur s'ouvre.<br />
								N.B.: Si vous s&eacute;lectionnez un titre, le dossier complet est charg&eacute; !</li>
							<li>En appuyant sur le bouton de lecture, un navigateur s'ouvre. Il fonctionne comme pr&eacute;c&eacute;demment.</li>
							<li>En chargeant un fichier .m3u s'il en existe d&eacute;j&agrave;</li>
							<li>En passant par l'explorateur, mais je le d&eacute;crirai plus loin</li>
						</ul>
					
					<p>Maintenant on va voir ce qui se cache derri&egrave;re le bouton "Liste de lecture".<br />
					Comme je suis s&ucirc;r que vous &ecirc;tes impatients, vous avez d&eacute;j&agrave; cliqu&eacute; dessus :p.<br />
					C'est dans cette page que vous irez les plus souvent. A l'int&eacute;rieur de celle-ci, vous pouvez :
					</p>	
						<ul>
							<li>S&eacute;lectionner les morceaux, les supprimer, les d&eacute;placer...</li>
							<li>Modifier le nom et les TAGs de chaque titre (bouton D&eacute;tails en bas ou un clique droit sur le titre)</li>
							<li>Enregistrer la liste dans un fichier m3u</li>
							<li>Associer une image &agrave; un titre</li>
						</ul>
					<p><a href="images/fux_liste.jpg" title="Liste de lecture de Fu(X)"><img class="image_fux_grand" src="images/fux_liste.jpg" alt="Liste de lecture de Fu(X)" /></a>
					</p>
					<p>Maintenant, on va voir ce qui se cache derri&egrave;re la partie Exploration !<br />
					Je mets directement un aper&ccedil;u de la zone :<br /><br />
					<a href="images/fux_exploration.jpg" title="Explorateur de Fu(X)"><img class="image_fux_grand" src="images/fux_exploration.jpg" alt="Explorateur de Fu(X)" /></a><br /><br />
					Je dois vous avouer une chose, enfin deux : le nom est barbare et faux !
					Il est faux car il faudrait mettre en th&eacute;orie un 's'. Pourquoi ? Simplement parce qu'il y a non pas un mais deux explorateurs de fichiers !<br />
					Chacun permet de visualiser un dossier, comme sur la capture, ou le contenu de la liste de lecture ou bien le contenu d'un fichier .m3u.<br />
					Pour acc&eacute;der &agrave; chacun, rien de plus simple : en haut, vous trouverez trois boutons "Mes Documents", "Ordinateur" et "Autre".
					Lorsque vous cliquez sur le premier, un sous menu apparait.
					La direction qui y est indiqu&eacute; correspond &agrave; l'explorateur qui sera utilis&eacute;.
					"Mes Documents" a pour r&eacute;f&eacute;rence le dossier mes documents, "Ordinateur" permet d'acc&eacute;der aux diff&eacute;rents lecteurs et "Autre" donne un acc&egrave;s direct aux fichiers .m3u enregistr&eacute;s &agrave; l'aide de Fu(X) et &agrave; la liste de lecture (comme sur la capture).<br />
					Et pour que le tout soit encore plus int&eacute;ressant, elles peuvent int&eacute;ragir entre elles ! Plusieurs solutions : le glisser-d&eacute;poser, le couper-copier-coller, la s&eacute;rie de bouton au milieu.<br />
					Attention, il existe certaines r&egrave;gles d'utilisations et qui d&eacute;pend de l'&eacute;tat de chacun des explorateurs.<br /><br />
					</p>
					<table id="regle_explo">
							<tr>
								<td class="gras"></td>
								<td class="gras" colspan="2">Dossier</td>
								<td class="gras" colspan="2">Fichier .m3u/liste de lecture</td>
							</tr>
							<tr>
								<td class="gras" rowspan="4">Dossier</td>
								<td>&lt;</td>
								<td>D&eacute;place un dossier/fichier de la droite vers la gauche</td>
								<td class="gauche">&lt;</td>
								<td>Indisponible</td>
							</tr>
							<tr>
								<td>=</td>
								<td>Copie un dossier/fichier de l'explorateur actif vers le non actif</td>
								<td class="gauche">=</td>
								<td>Indisponible</td>
							</tr>
							<tr>
								<td>&gt;</td>
								<td>D&eacute;place un dossier/fichier de la gauche vers la droite</td>
								<td class="gauche">&gt;</td>
								<td>Ajoute dans le fichier les titres s&eacute;lectionn&eacute;s dans le dossier</td>
							</tr>
							<tr>
								<td class="bas">X</td>
								<td class="bas">Supprime un dossier/fichier de l'explorateur actif</td>
								<td class="gaucheBas">X</td>
								<td class="bas">Supprime un dossier/fichier/ligne de l'explorateur actif</td>
							</tr>
							
							<tr>
								<td class="gras" rowspan="4">Fichier .m3u/liste de lecture</td>
								<td>&lt;</td>
								<td>Ajoute dans le fichier les titres s&eacute;lectionn&eacute;s dans le dossier</td>
								<td class="gauche">&lt;</td>
								<td>D&eacute;place les lignes s&eacute;lectionn&eacute;es de la droite vers la gauche</td>
							</tr>
							<tr>
								<td>=</td>
								<td>Indisponible</td>
								<td class="gauche">=</td>
								<td>Copie les lignes s&eacute;lectionn&eacute;es de l'explorateur actif vers le non actif</td>
							</tr>
							<tr>
								<td>&gt;</td>
								<td>Indisponible</td>
								<td class="gauche">&gt;</td>
								<td>D&eacute;place les lignes s&eacute;lectionn&eacute;es de la gauche vers la droite</td>
							</tr>
							<tr>
								<td>X</td>
								<td>Supprime un dossier/fichier/ligne de l'explorateur actif</td>
								<td class="gauche">X</td>
								<td>Supprime les lignes s&eacute;lectionn&eacute;es de l'explorateur actif</td>
							</tr>
						</table>
						<p>Il y a aussi les raccourcis :</p>
						<table id="racc_explo">
							<tr>
								<td>&lt;</td>
								<td>Gauche</td>
							</tr>
							<tr>
								<td>=</td>
								<td>F2</td>
							</tr>
							<tr>
								<td>&gt;</td>
								<td>Droite</td>
							</tr>
							<tr>
								<td>X</td>
								<td>Suppr</td>
							</tr>
						</table>
					<p>	Les raccourcis classiques fonctionnent : Alt+Gauche, Ctrl+R...</p>
					<p>Passons &agrave; la derni&egrave;re partie qui est l'une de mes pr&eacute;f&eacute;r&eacute;es.<br />
					On va maintenant dans "Pr&eacute;f&eacute;rences", et l'on tombe sur<br /><br />
					<a href="images/fux_couleur.jpg" title="Les pr&eacute;f&eacute;rences dans Fu(X)"><img class="image_fux_grand" src="images/fux_couleur.jpg" alt="Les pr&eacute;f&eacute;rences dans Fu(X)" /></a><br /><br />
					Ici, on se prend pour un artiste ! D'accord, c'est pas encore du Picasso mais &ccedil;a peut le devenir ;).<br />
					On v&eacute;rifie que la pastille est sur "modifier".
					Maintenant, s&eacute;lectionnez l'un des fichiers pr&eacute;sents dans la liste d&eacute;roulante puis faite appliquer tout en bas.
					Passez maintenant sur l'&eacute;cran principal et observez ;).
					</p>
					<h3>On s'&eacute;clate !</h3>
					<p><a href="images/fux_vueeclate.jpg" title="On s'&eacute;clate avec Fu(X) ;)"><img class="image_fux_grand" src="images/fux_vueeclate.jpg" alt="&Eacute;clatage de Fu(X)" /></a><br /><br />
					&Agrave; vous de d&eacute;courvir comment on fait !<br />
					Indice : c'est un probl&egrave;me de bouton.</p>
					<p>C'est maintenant la fin de ce petit tuto.
					J'esp&egrave;re que ce petit descriptif vous aura &eacute;t&eacute; utile pour la prise en main de certaines parties du logiciel ou m&ecirc;me de le d&eacute;couvrir et de vous avoir donn&eacute; envie de le t&eacute;l&eacute;charger !</p>
					<p class="droite">David, alias etrange02</p>
				</div>
			</div>
		</div>
		
		<?php include("piedPage.php"); ?>
		
	</body>
</html>