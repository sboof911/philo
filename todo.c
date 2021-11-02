// First  : if philo[id] eat he take fork[id] && fork[(id + 1) % info->number]
// Second : if philo has end of eating he drop fork[id] && fork[(id + 1) % info->number] && sleep
// Third : if philo has finished sleeping he beggin think until fork[id] && fork[(id + 1) % info->number] are availebale
// Forth : if philo last time he eated >= time to die the philo[id] die and the simulation stops