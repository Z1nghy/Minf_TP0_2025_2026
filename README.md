# Minf_TP0_2025_2026
## Timer

Le PIC 32 que nous utilisons à un clock de 80Mhz, cette fréquence nous avons besoin qu'elle soit beaucoup plus base pour le timer voulu de 100ms, pour ceci nous avons un prescaler, ce prescaler à plusieure valeur de division,  1, 8, 64 ou 256.
Ici nous allons utiliser 256, ce qu ifait que la fréquence st de 312.5kHz avec cette fréquence nous alons pouvoir completer la valeur dans le timer periode, cette valeur est pour dire combien de fois y'atil 312.5kHz dans 100ms.
Si nous transformons cette fréquence en temps avec 1/312500 , nous trouvons 3.2 us, et si nous divisons 100ms par ces 3.2us nous trouvons une valeur 31249 ce que nous allons mettre dans le timer period, voici quoi mettre dans le reste des cases:

<img width="507" height="283" alt="image" src="https://github.com/user-attachments/assets/6fde4dba-6e4f-4512-87c3-c787dbc5e619" />


## Mesures
### 3 secondes

Voici donc la mesure de mes trois secondes ou le code initialise avant de rentrer dans le cas APP_STATE_SERVICE_TASKS et de faire le chenillard 
<img width="1284" height="828" alt="image" src="https://github.com/user-attachments/assets/46b1b22c-1ab6-4806-a0c9-57fd5b9f6f58" />
Comme nous pouvons le voir nous avons les LEDs qui sont alum pour 3.075s ce qui correspond à la demande à ce que l'apelle de fonction du APP_UpdateState soit appelé apres 3 secondes:

<img width="615" height="73" alt="image" src="https://github.com/user-attachments/assets/39db130b-72bd-4972-8ef3-1fe959d63feb" />

### Le chenillard

Et voici la mesure pour le chenillard, comme nous pouvons le voir il se declanche juste après les trois secondes de la mesure précédante:
<img width="1285" height="839" alt="image" src="https://github.com/user-attachments/assets/58fb65fe-b7b5-4ebc-978c-dd7aec1afef7" />

Et comme démontrer ci-dessus le delta de temps mesuré sur le C2 (etat bas, c'est la que les LED's ont allumé) le temps est de ~200ms, ce qui est conforme avec la ligne demandant un cycle de 200ms, ce qui est aussi conforme à la donnée est le fait qu'ils s'allume un à un et s'eteigne just après.

<img width="559" height="55" alt="image" src="https://github.com/user-attachments/assets/daecab3c-f270-4254-a552-6de3334970dc" />




