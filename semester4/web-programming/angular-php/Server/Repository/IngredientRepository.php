<?php
require_once __DIR__ . '/../Datalink/DataLink.php';
require_once __DIR__ . '/../Model/Ingredient.php';

class IngredientRepository {
    private $dataLink;

    public function __construct() {
        $this->dataLink = new DataLink();
    }

    public function create($ingredientName, $ingredientQuantity, $ingredientMeasurementUnit, $ingredientRecipeId) {
        $query = "INSERT INTO Ingredient (Name, Quantity, MeasurementUnit, RecipeID) VALUES (?, ?, ?, ?)";
        $statement = $this->dataLink->prepare($query);
        $statement->bind_param("sisi", $ingredientName, $ingredientQuantity, $ingredientMeasurementUnit, $ingredientRecipeId);

        return $statement->execute();
    }

    public function getAll() {
        $query = "SELECT * FROM Ingredient";
        $result = $this->dataLink->execute($query);
        $ingredients = [];
        
        while ($row = $result->fetch_assoc()) {
            $ingredient = new Ingredient();
            $ingredient->IngredientID = $row['IngredientID'];
            $ingredient->Name = $row['Name'];
            $ingredient->Quantity = $row['Quantity'];
            $ingredient->MeasurementUnit = $row['MeasurementUnit'];
            $ingredient->RecipeID = $row['RecipeID'];
            $ingredients[] = $ingredient;
        }
        
        return $ingredients;
    }

    public function getById($id) {
        $query = "SELECT * FROM Ingredient WHERE IngredientID = ?";
        $statement = $this->dataLink->prepare($query);
        $statement->bind_param("i", $id);
        $statement->execute();
        $result = $statement->get_result();
        
        if ($row = $result->fetch_assoc()) {
            $ingredient = new Ingredient();
            $ingredient->IngredientID = $row['IngredientID'];
            $ingredient->Name = $row['Name'];
            $ingredient->Quantity = $row['Quantity'];
            $ingredient->MeasurementUnit = $row['MeasurementUnit'];
            $ingredient->RecipeID = $row['RecipeID'];
            return $ingredient;
        }
        
        return null;
    }

    public function getByRecipeId($recipeId) {
        $query = "SELECT * FROM Ingredient WHERE RecipeID = ?";
        $stmt = $this->dataLink->prepare($query);
        $stmt->bind_param("i", $recipeId);
        $stmt->execute();
        $result = $stmt->get_result();
        $ingredients = [];
        
        while ($row = $result->fetch_assoc()) {
            $ingredient = new Ingredient();
            $ingredient->IngredientID = $row['IngredientID'];
            $ingredient->Name = $row['Name'];
            $ingredient->Quantity = $row['Quantity'];
            $ingredient->MeasurementUnit = $row['MeasurementUnit'];
            $ingredient->RecipeID = $row['RecipeID'];
            $ingredients[] = $ingredient;
        }
        
        return $ingredients;
    }

    public function update($ingredient) {
        $query = "UPDATE Ingredient SET Name = ?, Quantity = ?, MeasurementUnit = ?, RecipeID = ? WHERE IngredientID = ?";
        $statement = $this->dataLink->prepare($query);
        $statement->bind_param("sisii", $ingredient->Name, $ingredient->Quantity, $ingredient->MeasurementUnit, $ingredient->RecipeID, $ingredient->IngredientID);

        return $statement->execute();
    }

    public function delete($id) {
        $query = "DELETE FROM Ingredient WHERE IngredientID = ?";
        $statement = $this->dataLink->prepare($query);
        $statement->bind_param("i", $id);
        return $statement->execute();
    }
}
?>