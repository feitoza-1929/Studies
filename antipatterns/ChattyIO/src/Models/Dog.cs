public class Dog
{
    public Guid Id { get; set; }
    public string Name { get; set; }
    public string Race { get; set; }
    public int Age { get; set; }
    public Guid OwnerId { get; set; }
    public Owner Owner { get; set; }
}