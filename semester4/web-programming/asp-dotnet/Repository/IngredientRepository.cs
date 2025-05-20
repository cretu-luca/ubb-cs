using asp_dotnet.Models;

namespace asp_dotnet.Repository;

public class IngredientRepository : BaseRepository<Ingredient>, IIngredientRepository
{
    public IngredientRepository(ApplicationDatabaseContext context)
        : base(context)
    {
    }
}