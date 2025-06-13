using asp_dotnet.Model;
using Microsoft.EntityFrameworkCore;

namespace asp_dotnet.Repository
{
    public class ProjectRepository : BaseRepository<Project>, IProjectRepository
    {
        public ProjectRepository(ApplicationDatabaseContext context) : base(context)
        {
        }

        public async Task<Project> GetProjectByName(string name)
        {
            return await context.Project.FirstOrDefaultAsync(p => p.Name == name);
        }
    }
}