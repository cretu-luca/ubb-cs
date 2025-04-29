<?php
    require_once __DIR__ . '/../Service/service.php';
    require_once __DIR__ . '/../Datalink/DataLink.php';
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
            case 'all':
                response(true, $service->getAllRecipes());
                break;
                
            case 'getById':
                if ($method !== 'GET') {
                    response(false, 'Method not allowed', 405);
                }

                $id = $_GET['id'] ?? null;
                if (!$id) {
                    response(false, 'Recipe ID required', 400);
                }
            
                $recipe = $service->getRecipeById($id);    
                if (!$recipe) { 
                    response(false, 'Recipe not found', 404);
                }
                
                response(true, $recipe);
                break;

            case 'getByAuthor':
                if ($method !== 'GET') {
                    response(false, 'Method not allowed', 405);
                }

                $author = $_GET['author'] ?? null;
                if (!$author) {
                    response(false, 'Author required', 400);
                }

                $recipes = $service->getRecipeByAuthor($author);
                response(true, $recipes);
                break;

            case 'getByType':
                if ($method !== 'GET') {
                    response(false, 'Method not allowed', 405);
                }

                $type = $_GET['type'] ?? null;
                if (!$type) {
                    response(false, 'Type required', 400);
                }

                $recipes = $service->getRecipeByType($type);
                response(true, $recipes);
                break;

            case 'getByName':
                if ($method !== 'GET') {
                    response(false, 'Method not allowed', 405);
                }

                $name = $_GET['name'] ?? null;
                if (!$name) {
                    response(false, 'Name required', 400);
                }

                $recipe = $service->getRecipeByName($name);
                response(true, $recipe);
                break;

            case 'create':
                if ($method !== 'POST') {
                    response(false, 'Method not allowed', 405);
                }
                
                $data = json_decode(file_get_contents('php://input'), true);
                
                $result = $service->createRecipe(
                    $data['name'] ?? '',
                    $data['author'] ?? '',
                    $data['type'] ?? '',
                    $data['instructions'] ?? ''
                );
                
                if (!$result) {
                    response(false, 'Failed to create recipe', 400);
                }
                
                response(true, 'Recipe created', 201);
                break;
                
            case 'update':
                if ($method !== 'PUT') {
                    response(false, 'Method not allowed', 405);
                }
                $data = json_decode(file_get_contents('php://input'), true);
                
                if (empty($data['RecipeID'])) {
                    response(false, 'Recipe ID required', 400);
                }
                
                $recipe = new Recipe();
                $recipe->RecipeID = $data['RecipeID'];
                $recipe->Name = $data['Name'] ?? '';
                $recipe->Author = $data['Author'] ?? '';
                $recipe->Type = $data['Type'] ?? '';
                $recipe->Instructions = $data['Instructions'] ?? '';
                
                if (!$recipe->isValid()) {
                    response(false, 'Invalid recipe data', 400);
                }
                if (!$service->updateRecipe($recipe)) {
                    response(false, 'Update failed', 500);
                }
                
                response(true, 'Recipe updated');
                break;
                
            case 'delete':
                if ($method !== 'DELETE') {
                    response(false, 'Method not allowed', 405);
                }
                
                $id = $_GET['id'] ?? null;
                if (!$id) response(false, 'Recipe ID required', 400);
                
                if (!$service->deleteRecipe($id)) {
                    response(false, 'Delete failed', 500);
                }
                
                response(true, 'Recipe deleted');
                break;
                
            default:
                response(false, 'Unknown action', 404);
        }
    } catch (Exception $e) {
        response(false, $e->getMessage(), 500);
    }
?>