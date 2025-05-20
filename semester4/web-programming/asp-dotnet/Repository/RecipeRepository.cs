using asp_dotnet.Models;

namespace asp_dotnet.Repository;

public class RecipeRepository : BaseRepository<Recipe>, IRecipeRepository
{
    public RecipeRepository(ApplicationDatabaseContext context)
        : base(context)
    {
    }
}