using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication3;
using WebApplication3.Models;

namespace MyApp.Namespace
{
    public class MemberOfModel : PageModel
    {
        private readonly AppDbContext _context;
        public ICollection<Project> Projects { get; set; }

        public MemberOfModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
            ICollection<Project> allProjects = _context.Projects.ToList();
            ICollection<Project> projects = new List<Project>();
            
            String username = HttpContext.Session.GetString("username");
            int usernameId = _context.Developers.Where(d => d.Name == username).Select(d => d.Id).FirstOrDefault();

            foreach (var project in allProjects)
            {
                List<String> membersIds = project.Members.Split(", ").ToList();

                foreach (var memberId in membersIds)
                {
                    if (memberId.Trim().Equals(usernameId.ToString()))
                    {
                        projects.Add(project);
                    }
                }
            }
            
            Projects = projects;
        }
    }
}
