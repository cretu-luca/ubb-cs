using Microsoft.AspNetCore.Mvc;
using asp_dotnet.Models;
using asp_dotnet.Repository;

using asp_dotnet.Controllers;

[Route("[controller]")]
[ApiController]
public class IngredientController : BaseController<Ingredient>
{
    private IIngredientRepository ingredientRepository;

    public IngredientController(IIngredientRepository ingredientRepository)
        : base(ingredientRepository)
    {
        this.ingredientRepository = ingredientRepository;
    }
}