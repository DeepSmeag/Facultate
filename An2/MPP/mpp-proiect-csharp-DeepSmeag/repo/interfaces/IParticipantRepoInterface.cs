﻿using mpp_proiect_csharp_DeepSmeag.domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace mpp_proiect_csharp_DeepSmeag.repo.interfaces
{
    internal interface IParticipantRepoInterface : IRepoInterface<Participant, int>
    {
        Participant getParticipantByName(String name);
        List<Participant> getParticipantsByAgeCategory(int ageMin, int ageMax);
        List<Participant> getParticipantsByProba(int idProba);
    }
}
