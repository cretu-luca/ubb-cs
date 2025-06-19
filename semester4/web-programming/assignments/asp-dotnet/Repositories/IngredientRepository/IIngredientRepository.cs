using asp_dotnet.Models;

namespace asp_dotnet.Repository;

public interface IIngredientRepository : IBaseRepository<Ingredient>
{
    Task<IEnumerable<Ingredient>> GetIngredientsByRecipeID(int id);
}