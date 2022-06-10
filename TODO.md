# TODO list

Cette liste pourra vous guider dans le choix des étapes de refactoring en présentant les refactoring majeurs à faire sur le code.

## Rendre la liste chaînée compatible avec les appels du vector

Cette tâche doit permettre d'utiliser la liste comme le vecteur. Pour le permettre, il est nécessaire :
 - de renommer `add_value` en `push_back`
 - de renommer `clear_list` en `clear`
 - d'ajouter un iterateur à la classe, ainsi que les méthodes `begin` et `end` permettant de parcourir la liste, ainsi que l'opérateur `++` pour ces itérateurs.
 - d'ajouter l'opérateur `[]` pour accéder à une valeur par sa position.

## Utilisation d'un manager pour les ressources

Le manager est responsable de créer des objets, et de gérer leur cycle de vie. Le manager peut notamment avoir plusieurs factory pour les différents rôles (sources de données, type de stockage, sortie, type de calcul à effectuer)

## Injection de dépendances

Jusqu'à cette tâche, les modifications ne changent pas réellement le fonctionnement du programme. À partir de cette étape, on va rendre le programme plus facile à modifier et à tester. L'idée est d'avoir un flux de type lire -> stocker -> traiter -> écrire où chaque étape peut être paramétrée en injectant l'objet requis dans le flux. Un nouvel objet va donc être nécessaire, ainsi que des interfaces pour chaque rôle. Une bonne illustration pourrait être le code suivant :

```cpp
int main() {
	storage_type storage; // change storage type if required
	storage = load_bin(path_to_file); // change load_bin to load_text for text source
	storage_type compute_result = average(storage); // change function name to change behaviour
	write_text(compute_result); // change to write_bin to output in bin, to display for screen output
	return 0;
}
```

Le code si dessus est inutilement complexe, difficile à maintenir, à flexibiliser et à tester. Un bon code serait semblable à :

```cpp
class storage_type { // pure virtual
	/* Declarations */
};
// list_storage, vector_storage inherit from storage_type

class loader { // pure virtual
}; // as for storage_type, text and bin loaders are children of loader

class calculation { // pure virtual
}; // average, rolling_average, etc. inherit from calculation

class writer { // pure virtual
}; // any output (file - text or bin, screen) inherit from this one

class process { // raw pointers may be improved
	storage_type *_storage;
	loader *_loader;
	calculation *_calc;
	writer *_writer;
	
public:
	process(storage_type *stor, loader *load, calculation *calc, writer *write);
	void execute();
};
```

Il sera nécessaire, notamment pour le `storage_type`, d'exposer les méthodes communes aux classes sous-jacentes (opérateur d'accès `[]`, begin, end, iterator, etc.) pour permettre l'accès à ces méthodes au travers de l'interface.

Simplement, le manager crée (grâce aux factories), une instance de chaque élément nécessaire (il pourrait y en avoir plus ou moins), puis instancie un objet de type process auquel chaque instance des éléments requis. Puis, le main appelle la méthode `execute` qui réalise les appels aux différentes étapes :

```cpp
void process::execute() {
	// /!\ Think of checking for nullptr first
	*_storage = _loader->load(path_to_file);
	_calc->compute(_storage);
	_writer->write(_storage);
}
```

Et dans le main :

```cpp
int main() {
	resource_manager mgr{};
	// Next line can be parameterized
	process p{mgr.make_storage(LIST),
			  mgr.make_reader(BIN),
			  mgr.make_calculation(AVG),
			  mgr.make_writer(TEXT)};
	p.execute();
	mgr.clear_resources();
	return 0;
}
```

Avec une implémentation correcte (attention aux pointeurs natifs, à RAII, etc.), le programme devrait pouvoir s'exécuter avec des paramètres différents sans problème et sans fuite mémoire (tester avec valgrind).

## Ajout de tests

Les dépendances du programme étant injectées et donc construites en dehors du flux d'exécution de l'algorithme, tout peut maintenant être testé plus facilement. À l'aide de l'API cppunit, ajouter des tests unitaires sur vos classes. Pour tester les fonctions de calcul, il est maintenant facile de construire des objets de type `storage_type` pour les passer en paramètre des fonctions de calcul et vérifier le résultat.

## Ajout de commentaires

Avec une syntaxe doxygen, écrire les commentaires des classes et des fonctions pour générer la documentation du code.
