<?php
    require_once __DIR__ . '/../Repository/RecipeRepository.php';
    require_once __DIR__ . '/../Repository/IngredientRepository.php';
    require_once __DIR__ . '/../Model/Recipe.php';
    require_once __DIR__ . '/../Model/Ingredient.php';

    class Service {
        public $ingredientRepository;
        public $recipeRepository;

        function __construct() {
            $this->ingredientRepository = new IngredientRepository();
            $this->recipeRepository = new RecipeRepository();
        }
    
        function getAllRecipes() {
            return $this->recipeRepository->getRecipes();
        }
        
        function getRecipeById($id) {
            return $this->recipeRepository->getRecipeById($id);
        }

        function getRecipeByAuthor($author) {
            return $this->recipeRepository->getRecipeByAuthor($author);
        }

        function getRecipeByType($type) {
            return $this->recipeRepository->getRecipeByType($type);
        }

        function createRecipe($name, $author, $type, $instructions, $date) {
            if (empty($name) || empty($author) || empty($type) || empty($instructions) || empty($date)) {
                return false;
            }
            
            return $this->recipeRepository->createRecipe($name, $author, $type, $instructions, $date);
        }
        
        function updateRecipe($recipe) {
            if (!$recipe->isValid()) {
                return false;
            }
            
            return $this->recipeRepository->updateRecipe($recipe);
        }
        
        function deleteRecipe($recipeId) {
            if (empty($recipeId)) {
                return false;
            }
            
            return $this->recipeRepository->deleteRecipe($recipeId);
        }
        
        function recipeExists($recipe) {
            return $this->recipeRepository->exists($recipe);
        }
        
        function getAllIngredients() {
            return $this->ingredientRepository->getAll();
        }
        
        function getIngredientById($ingredientId) {
            if (empty($ingredientId)) {
                return null;
            }
            
            return $this->ingredientRepository->getById($ingredientId);
        }

        function getIngredientsByRecipeId($recipeId) {
            if (empty($recipeId)) {
                return null;
            }
            
            return $this->ingredientRepository->getByRecipeId($recipeId);
        }
        
        function createIngredient($ingredientName, $ingredientQuantity, $ingredientMeasurementUnit, $ingredientRecipeId) {
            if (empty($ingredientName) || 
                empty($ingredientQuantity) || 
                empty($ingredientMeasurementUnit) || 
                empty($ingredientRecipeId)) {
                return false;
            }
            
            return $this->ingredientRepository->create($ingredientName, $ingredientQuantity, $ingredientMeasurementUnit, $ingredientRecipeId);
        }
    }
?>