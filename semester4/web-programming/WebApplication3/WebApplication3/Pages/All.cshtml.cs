using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication3;
using WebApplication3.Models;

namespace MyApp.Namespace
{
    public class AllModel : PageModel
    {
        private readonly AppDbContext _context;
        public ICollection<Project> Projects { get; set; }

        public AllModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {   
            Projects = _context.Projects.ToList();
        }
    }
}
