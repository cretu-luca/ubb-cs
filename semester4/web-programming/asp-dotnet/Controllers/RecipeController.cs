using Microsoft.AspNetCore.Mvc;
using asp_dotnet.Models;
using asp_dotnet.Repository;

using asp_dotnet.Controllers;

[Route("[controller]")]
[ApiController]
public class RecipeController : BaseController<Recipe>
{
    private IRecipeRepository recipeRepository;

    public RecipeController(IRecipeRepository recipeRepository)
        : base(recipeRepository)
    {
        this.recipeRepository = recipeRepository;
    }
}