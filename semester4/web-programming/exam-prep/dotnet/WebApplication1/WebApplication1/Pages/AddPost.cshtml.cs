using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using WebApplication1;
using WebApplication1.Models;

namespace MyApp.Namespace
{
    public class AddPostModel : PageModel
    {
        private readonly AppDbContext _context;

        public AddPostModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
        }

        public IActionResult OnPost()
        {
            String username = HttpContext.Session.GetString("username");
            String topicName = Request.Form["topicName"];
            String text = Request.Form["text"];
            String date = "15062025";
             
            Topic topic = _context.Topics.FirstOrDefault(t => t.Name == topicName);
                
            if (topic == null)
            {
                topic = new Topic { Name = topicName };
                _context.Topics.Add(topic);
                _context.SaveChanges();
            }
            
            var post = new Post
            {
                User = username,
                TopicId = topic.Id,
                Text = text,
                Date = int.Parse(date)
            };
            
            _context.Posts.Add(post);
            _context.SaveChanges();
            
            return RedirectToPage("/Home");
        }
    }
}
