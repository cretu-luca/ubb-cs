using asp_dotnet.Models;
using Microsoft.EntityFrameworkCore;

namespace asp_dotnet.Repository;

public class RecipeRepository : BaseRepository<Recipe>, IRecipeRepository
{
    public RecipeRepository(ApplicationDatabaseContext context)
        : base(context)
    {
    }

    public async Task<IEnumerable<Recipe>> GetRecipesByAuthor(string author)
    {
        return await this.context.Recipe
            .Where(recipe => recipe.Author == author)
            .ToListAsync();
    }

    public async Task<IEnumerable<Recipe>> GetRecipesByType(string type)
    {
        return await this.context.Recipe
            .Where(recipe => recipe.Type == type)
            .ToListAsync();
    }
}