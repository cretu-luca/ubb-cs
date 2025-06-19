<?php
require_once __DIR__ . '/../Datalink/DataLink.php';

class RecipeRepository {
    public $datalink;

    function __construct() {
        $this->datalink = new DataLink();
    }

    // create
    function createRecipe($name, $author, $type, $instructions, $date) {
        $query = "INSERT INTO Recipe (Name, Author, Type, Instructions, Date) VALUES (?, ?, ?, ?, ?)";
        $statement = $this->datalink->prepare($query);
        $statement->bind_param("sssss", $name, $author, $type, $instructions, $date);

        return $statement->execute();
    }

    // read
    function getRecipes() {
        $query = "SELECT * FROM Recipe";
        $statement = $this->datalink->prepare($query);
        $statement->execute();

        return $statement->get_result()->fetch_all(MYSQLI_ASSOC);
    }

    function getRecipeById($recipeID) {
        $query = "SELECT * FROM Recipe WHERE RecipeID = ?";
        $statement = $this->datalink->prepare($query);
        $statement->bind_param("i", $recipeID);
        $statement->execute();

        return $statement->get_result()->fetch_assoc();
    }

    function getRecipeByAuthor($author) {
        $query = "SELECT * FROM Recipe WHERE Author = ?";
        $statement = $this->datalink->prepare($query);
        $statement->bind_param("s", $author);
        $statement->execute();
        
        return $statement->get_result()->fetch_all(MYSQLI_ASSOC);
    }

    function getRecipeByType($type) {
        $query = "SELECT * FROM Recipe WHERE Type = ?";
        $statement = $this->datalink->prepare($query);
        $statement->bind_param("s", $type);
        $statement->execute();

        return $statement->get_result()->fetch_all(MYSQLI_ASSOC);
    }

    // update        
    function updateRecipe($recipe) {
        $query = "UPDATE Recipe SET Name = ?, Author = ?, Type = ?, Instructions = ?, Date = ? WHERE RecipeID = ?";
        $statement = $this->datalink->prepare($query);
        $statement->bind_param("sssssi", $recipe->Name, $recipe->Author, $recipe->Type, $recipe->Instructions, $recipe->Date, $recipe->RecipeID);

        return $statement->execute();
    }

    // delete
    function deleteRecipe($recipeID) {
        $query = "DELETE FROM Recipe WHERE RecipeID = ?";
        $statement = $this->datalink->prepare($query);
        $statement->bind_param("i", $recipeID);
        
        return $statement->execute();
    }

    // 
    function exists($recipe) {
        $query = "SELECT COUNT(*) as count FROM Recipe WHERE Name = ? AND Author = ? AND Type = ? AND Instructions = ? AND Date = ?";
        $statement = $this->datalink->prepare($query);
        $statement->bind_param("ssss", $recipe->Name, $recipe->Author, $recipe->Type, $recipe->Instructions, $recipe->Date);
        $statement->execute();

        $result = $statement->get_result();
        $row = $result->fetch_assoc();

        return ($row['count'] > 0);
    }
}
?>