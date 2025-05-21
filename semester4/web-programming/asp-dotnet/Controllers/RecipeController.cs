using Microsoft.AspNetCore.Mvc;
using asp_dotnet.Models;
using asp_dotnet.Repository;
using Microsoft.AspNetCore.Authorization;

namespace asp_dotnet.Controllers
{
    [Authorize]
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

        [HttpGet("GetRecipesByAuthor/{author}")]
        public async Task<IEnumerable<Recipe>> GetRecipesByAuthor(string author)
        {
            return await this.recipeRepository.GetRecipesByAuthor(author);
        }

        [HttpGet("GetRecipesByType/{type}")]
        public async Task<IEnumerable<Recipe>> GetRecipesByType(string type)
        {
            return await this.recipeRepository.GetRecipesByType(type);
        }
    }
}