namespace WebApplication1.Models;

public class Topic
{
    public int Id { get; set; }
    public String Name { get; set; }
    public ICollection<Post> Posts { get; set; }
}