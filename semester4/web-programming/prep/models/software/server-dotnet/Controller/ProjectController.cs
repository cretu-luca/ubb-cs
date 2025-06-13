using asp_dotnet.Repository;
using asp_dotnet.Model;
using Microsoft.AspNetCore.Mvc;
using System.Linq;
using System.Text.Json;

namespace asp_dotnet.Controller
{
    [Route("[controller]")]
    [ApiController]
    public class ProjectController : BaseController<Project>
    {
        private readonly IProjectRepository projectRepository;

        public ProjectController(IProjectRepository repository) : base(repository)
        {
            projectRepository = repository;
        }

        [HttpPost("Assign")]
        public async Task<ActionResult> Assign([FromBody] JsonElement request)
        {
            try
            {
                string userid = request.GetProperty("userid").GetString() ?? "";
                string projectNames = request.GetProperty("projectNames").GetString() ?? "";
                
                if (string.IsNullOrEmpty(userid) || string.IsNullOrEmpty(projectNames))
                {
                    return BadRequest("User ID and project names are required");
                }
                
                string[] projectNamesArray = projectNames.Split(',');

                foreach (string projectName in projectNamesArray)
                {
                    string trimmedProjectName = projectName.Trim();
                    if (string.IsNullOrEmpty(trimmedProjectName)) continue;
                    
                    var project = await projectRepository.GetProjectByName(trimmedProjectName);
                    if (project == null)
                    {
                        project = new Project 
                        { 
                            Name = trimmedProjectName, 
                            Members = userid,
                            ProjectManagerID = 1,
                            Description = "Auto-created project"
                        };
                        await projectRepository.AddAsync(project);
                    }
                    else
                    {
                        project.Members += $",{userid}";
                        await projectRepository.UpdateAsync(project);
                    }
                }
                return Ok($"User {userid} assigned to projects: {string.Join(", ", projectNamesArray.Select(p => p.Trim()).Where(p => !string.IsNullOrEmpty(p)))}"); 
            }
            catch (Exception ex)
            {
                var innerException = ex.InnerException?.Message ?? "No inner exception";
                return StatusCode(500, $"Internal server error: {ex.Message}. Inner: {innerException}");
            }
        }
    }
} 