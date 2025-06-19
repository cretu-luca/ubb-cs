using asp_dotnet.Models;
using Microsoft.EntityFrameworkCore;

namespace asp_dotnet.Repository;

public class IngredientRepository : BaseRepository<Ingredient>, IIngredientRepository
{
    public IngredientRepository(ApplicationDatabaseContext context)
        : base(context)
    {
    }

    public async Task<IEnumerable<Ingredient>> GetIngredientsByRecipeID(int id)
    {
        return await context.Ingredient
            .Where(ingredient => ingredient.RecipeId == id)
            .ToListAsync();
    }
}