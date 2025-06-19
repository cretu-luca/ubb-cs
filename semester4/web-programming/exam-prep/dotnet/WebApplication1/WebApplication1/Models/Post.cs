namespace WebApplication1.Models;

public class Post
{
    public int Id { get; set; }
    public String User { get; set; }
    public int TopicId { get; set; }
    public String Text { get; set; }
    public int Date { get; set; }
    public Topic Topic { get; set; }
}