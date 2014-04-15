			<div id="droite">
			<?php
				$connecte = false;
				
				if (isset($_POST['deconnexion']))
				{
					unset($_SESSION['admin']);
					unset($_SESSION['idpseudo']);
					unset($_SESSION['pseudo']);
					unset($_SESSION['mdp']);
					unset($_SESSION['autorise']);
				}
				
				if (isset($_POST['valideConnexion']) && isset($_POST['pseudo']) && isset($_POST['mdp']))
				{
					$pseudo = htmlentities($_POST['pseudo'], ENT_QUOTES, 'UTF-8');
					$mdp = htmlentities($_POST['mdp'], ENT_QUOTES, 'UTF-8');
					
					$resultat = $bdd->query('SELECT * FROM utilisateur WHERE pseudo="'.$pseudo.'"');
					$ligne = $resultat->fetch();
					
					if (strcmp($ligne['mdp'], $mdp) == 0)
					{
						$_SESSION['pseudo'] = $pseudo;
						$_SESSION['mdp'] = $mdp;						
						$_SESSION['admin'] = ($ligne['admin'] == 1);
						$_SESSION['idpseudo'] = $ligne['id'];
						$_SESSION['autorise'] = ($ligne['autorise'] == 1);
					}
					else
						echo '<p>Pseudo ou mot de passe erron&eacute;</p>';
					$resultat->closeCursor();
				}
				
				if (!empty($_SESSION['pseudo']) && !empty($_SESSION['mdp']))
					$connecte = true;
					
				if (!$connecte)
				{
			?>
				<form action="<?php echo $page_actuelle; ?>" method="post" title="Connectez-vous rapidement">
					<fieldset>
						<legend>Connexion rapide</legend>
						<label for="idpseudo">Pseudo</label><br />
						<input type="text" name="pseudo" id="idpseudo" maxlength="255"/><br />
						<label for="idmdp">Mot de passe</label><br />
						<input type="password" name="mdp" id="idmdp" maxlength="255"/><br />
						<input type="submit" value="Se connecter" name="valideConnexion" />
					</fieldset>
				</form>
				<hr />
				<form method="post" action="inscription.php" title="S'inscrire">
					<p>
						Vous n'&ecirc;tes pas encore inscrit ?
						<input type="submit" name="inscription" value="S'inscrire" />
					</p>
				</form>
				<p><a href="mot_passe_perdu.php">Mot de passe perdu ?</a></p>
			<?php
				}
				else
				{
					echo '<h3>'.$_SESSION['pseudo'].'</h3>';
			?>
				<table id="compte">
					<tr>
						<td>
						<form action="compte.php" method="post" title="Acc&eacute;der &agrave; mes param&egrave;tres">
							<p>
								<input type="submit" value="Mon compte" />
							</p>
						</form>
						</td>
						<td>
						<form action="<?php echo $page_actuelle; ?>" method="post">
							<p>
								<input type="submit" value="D&eacute;connexion" name="deconnexion" />
							</p>
						</form>
						</td>
					</tr>
					<?php
						if(isset($_SESSION['admin']) && $_SESSION['admin'])
						{
							echo '<tr><td colspan="2">';
							echo '<form action="./admin/index.php" method="post">
									  <p>
									  	  <input type="submit" value="Administration" />
									  </p>
								  </form>';
							echo '</td></tr>';
						}
					?>
				</table>
			<?php
				}
			?>
			</div>
