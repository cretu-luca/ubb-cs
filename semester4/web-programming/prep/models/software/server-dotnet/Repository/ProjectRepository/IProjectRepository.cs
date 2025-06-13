using asp_dotnet.Model;

namespace asp_dotnet.Repository
{
    public interface IProjectRepository : IBaseRepository<Project>
    {
        Task<Project> GetProjectByName(string name);
    }
}