

namespace QueueService;

public class MonitorLoop
{
    private readonly ILogger<MonitorLoop> _logger;
    private readonly IBackgroundTaskQueue _taskQueue;
    private readonly CancellationToken _cancellationToken;

    public MonitorLoop(ILogger<MonitorLoop> logger, IBackgroundTaskQueue taskQueue, IHostApplicationLifetime applicationLifetime)
    {
        _logger = logger;
        _taskQueue = taskQueue;
        _cancellationToken = applicationLifetime.ApplicationStopping;
    }

    public void Run()
    {
        _logger.LogInformation($"{nameof(MonitorAsync)} loop is starting now");
        Task.Run(async () => await MonitorAsync());
    }

    private async ValueTask MonitorAsync()
    {
        while(!_cancellationToken.IsCancellationRequested)
        {
            if(Console.ReadKey().Key is ConsoleKey.W)
            {
                await _taskQueue.QueueAsync(BuildWorkItemAsync);
            }
        }
    }

    private async ValueTask BuildWorkItemAsync(CancellationToken token)
    {
        var delayLoop = 0;
        var id = Guid.NewGuid();

        while (!token.IsCancellationRequested && delayLoop < 3)
        {
            try
            {
                await Task.Delay(5, token); 
            }
            catch (OperationCanceledException)
            {
            }

            delayLoop++;
            _logger.LogInformation($"Queued work item {id} is running. {delayLoop}/3");
        }

        var taskResult = delayLoop switch
        {
            3 => $"Queued Background Task {id} is complete",
            _ => $"Queued Background Task was cancelled"
        };

        _logger.LogInformation(taskResult);
    }
}