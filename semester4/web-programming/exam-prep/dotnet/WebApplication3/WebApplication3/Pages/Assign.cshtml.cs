using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication3;
using WebApplication3.Models;

namespace MyApp.Namespace
{
    public class AssignModel : PageModel
    {
        
        private readonly AppDbContext _context;
        public string message { get; set; }

        public AssignModel(AppDbContext context)
        {
            _context = context;
            message = ""; 
        }
        
        public void OnGet()
        {
        }

        public void OnPost()
        {
            String name =  Request.Form["name"];
            String projectsNames = Request.Form["projects"];
            List<String> projectsNamesArray = projectsNames.Split(",").ToList();

            String currentUsername = HttpContext.Session.GetString("username");
            SoftwareDeveloper currentUser = _context.Developers.Where(d => d.Name == currentUsername).FirstOrDefault();
            int currentUserId = currentUser.Id;
            
            Console.WriteLine(currentUser);
            
            SoftwareDeveloper user = _context.Developers.FirstOrDefault(x => x.Name == name);
            if (user == null)
            {
                message = "Name not found";
                return;
            }

            if (user.Id == currentUserId)
            {
                message = "Cannot assign projects to yourself";
                return;
            }

            foreach (String projectName in projectsNamesArray)
            {
                Project project = _context.Projects.Where(p => p.Name == projectName).FirstOrDefault();
                bool isMember = false;
                    
                if (project != null)
                {
                    List<String> membersIdsList = project.Members.Split(",").ToList();

                    foreach (String memberId in membersIdsList)
                    {
                        if (memberId.Trim().Equals(user.Id.ToString()))
                        {
                            // dont add
                            isMember = true; 
                        }
                    }

                    if (!isMember)
                    {
                        String membersIds = project.Members;
                        membersIds = membersIds + currentUser + ", ";
                        project.Members = membersIds;
                        _context.Update(project);
                        _context.SaveChanges();
                    }
                }
                else
                {
                    Project newProject = new Project();
                    newProject.Name = projectName.Trim();
                    newProject.Members = user.Id + ",";
                    newProject.Description = "desc";
                    newProject.ProjectManagerId = currentUserId;
                    
                    _context.Add(newProject);
                    _context.SaveChanges();
                }
            }
        }
    }
}
