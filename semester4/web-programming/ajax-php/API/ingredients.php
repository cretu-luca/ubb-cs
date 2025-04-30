<?php
    require_once __DIR__ . '/../Service/service.php';
    header('Content-Type: application/json');

    header("Access-Control-Allow-Origin: *");
    header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
    header("Access-Control-Allow-Headers: Content-Type");

    if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
        http_response_code(200);
        exit();
    }

    $service = new Service();
    $action = $_GET['action'] ?? '';
    $method = $_SERVER['REQUEST_METHOD'];

    function response($success, $data = null, $status = 200) {
        http_response_code($status);
        echo json_encode(['success' => $success, 'data' => $data]);
        exit;
    }

    try {
        switch ($action) {
            case 'getIngredientsByRecipeId':
                if ($method !== 'GET') {
                    response(false, 'Method not allowed', 405);
                }

                $recipeId = $_GET['recipeId'] ?? null;
                if (!$recipeId) {
                    response(false, 'Recipe ID required', 400);
                }

                $ingredients = $service->getIngredientsByRecipeId($recipeId);
                if (!$ingredients) {
                    response(false, 'No ingredients found for this recipe', 404);
                }
                
                response(true, $ingredients);
                break;

            case 'create':
                if ($method !== 'POST') {
                    response(false, 'Method not allowed', 405);
                }

                $data = file_get_contents('php://input');
                $ingredient = json_decode($data, true);
                
                if (!$ingredient) {
                    response(false, 'Invalid JSON data: ' . json_last_error_msg(), 400);
                }

                $name = $ingredient['Name'] ?? '';
                $quantity = $ingredient['Quantity'] ?? 0;
                $measurementUnit = $ingredient['MeasurementUnit'] ?? '';
                $recipeId = $ingredient['RecipeID'] ?? 0;
                
                $result = $service->createIngredient($name, $quantity, $measurementUnit, $recipeId);
                if (!$result) {
                    response(false, 'Failed to create ingredient', 400);
                }
                
                response(true, 'Ingredient created successfully');
                break;  

            default:
                response(false, 'Invalid action', 400);
        }
    } catch (Exception $e) {
        response(false, $e->getMessage(), 500);
    }
?>