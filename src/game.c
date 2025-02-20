// gcc src/game.c -o builds/game.exe && ./builds/game.exe

#include <stdio.h>
#include <stdlib.h>

// binärbaum ist hier komplett unnötig aber wollte einfach probieren

typedef struct Node
{
  int value;
  struct Node *left;
  struct Node *right;
} Node;

Node *create_node(int guess)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->value = guess;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

int height(Node *root)
{
  if (root == NULL)
    return 0;
  int left_height = height(root->left);
  int right_height = height(root->right);
  return (left_height > right_height ? left_height : right_height) + 1;
}

void print_spaces(int count)
{
  for (int i = 0; i < count; i++)
    printf(" ");
}

void print_level(Node *root, int level, int space)
{
  if (root == NULL)
  {
    // wenn kein knoten existiert dann einfach leerzeichen drucken
    print_spaces(space);
    printf(" ");
    return;
  }

  if (level == 1)
  {                      // auf der aktuellen ebene den knoten ausgeben
    print_spaces(space); // formatierung
    printf("%d", root->value);
  }
  else if (level > 1)
  { // ebene ist tiefer, also drucken wir rekursiv die linke und rechte seite des baums auf der entsprechenden ebene
    print_level(root->left, level - 1, space / 2);
    print_level(root->right, level - 1, space / 2);
  }
}

// finalen binärbaum drucken
void print_tree(Node *root)
{
  int h = height(root);
  int space = 20; // start abstand

  for (int i = 1; i <= h; i++)
  {
    print_spaces(space / 2);
    print_level(root, i, space);
    printf("\n");
    space /= 2;
  }
}

void free_tree(Node *tree)
{
  if (tree == NULL)
    return;
  free_tree(tree->left);
  free_tree(tree->right);
  free(tree);
}

void play_game(int max)
{
  Node *root = NULL;
  int min = 0;
  int my_guess;
  char response;

  while (1)
  {
    my_guess = min + (max - min) / 2; // max_range: 100 => 50

    if (root == NULL)
      root = create_node(my_guess);

    printf("Ist deine Nummer: %d?\n", my_guess);
    printf("Antwortmöglichkeiten: Niedriger: 'l'; Höher: 'h'; Richtig:'c'\n");
    scanf(" %c", &response);

    if (response == 'l')
    {
      // zahl ist größer, also nach rechts
      Node *current = root;
      while (current->right != NULL)
        current = root->right;
      current->right = create_node(my_guess);
      max = my_guess - 1;
    }
    else if (response == 'h')
    {
      // zahl ist kleiner, also nach links
      Node *current = root;
      while (current->left != NULL)
        current = root->left;
      current->left = create_node(my_guess);
      min = my_guess + 1;
    }
    else if (response == 'c')
    {
      printf("JAAAAAAAAAA! RICHTIIIIG GEILOMATIKO\n");
      printf("hier der baum:\n");
      print_tree(root);
      printf("\n");
      break;
    }
    else
    {
      printf("Falscher Input!\n");
      printf("Valide Inputs: 'l';'h';'c'\n");
    }

    if (min > max)
    {
      printf("du hast alle zahlen abgelehnt?????\n");
      printf("alles komplett falsch gelaufen garnicht geilomat\n");
      break;
    }
  }

  free_tree(root);
}

int main()
{
  int max_range;
  printf("Ich werde probieren deine Nummer zu erraten.\n");
  printf("  Schreibe: 'l' für Niedriger\n");
  printf("  Schreibe: 'h' für Höher\n");
  printf("  Schreibe: 'c' für RICCCHTTIIIIIG\n\n");
  printf("Was ist deine maximale Zahl?:\n");
  scanf("%d", &max_range);

  play_game(max_range);

  return 0;
}