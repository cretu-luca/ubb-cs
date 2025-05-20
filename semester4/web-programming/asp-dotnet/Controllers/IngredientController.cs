using Microsoft.AspNetCore.Mvc;
using asp_dotnet.Models;
using asp_dotnet.Repository;
using Microsoft.AspNetCore.Authorization;

namespace asp_dotnet.Controllers
{
    [Authorize]
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

        [HttpGet("GetIngredientsByRecipeID/{id}")]
        public async Task<IEnumerable<Ingredient>> GetIngredientsByRecipeID(int id)
        {
            return await ingredientRepository.GetIngredientsByRecipeID(id);
        }
    }
}