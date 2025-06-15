using asp_dotnet.Model;

namespace asp_dotnet.Repository
{
    public interface IUserRepository : IBaseRepository<User>
    {
        User? GetByUsername(string username);
    }
} 